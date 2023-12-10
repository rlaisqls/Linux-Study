#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SW_BLOCKS 10
#define MAX_PARAMETERS 3

typedef struct {
    pid_t pid;
    time_t lastRestartTime;
    int restartCount;
    char name[20];
    char parameters[MAX_PARAMETERS][20];
    char reason[50];
} SwBlock;

SwBlock blocks[MAX_SW_BLOCKS];
int swBlockCount;

void initLog() {
    FILE *log = fopen("log.txt", "a");
    fprintf(log, "SW Block Name | Restart cnt | Start Time           | Reason\n");
    fprintf(log, "========================================================================================\n");
    printf("SW Block Name | Restart cnt | Start Time           | Reason\n");
    printf("========================================================================================\n");
    fclose(log);
}

void printLog(SwBlock* block) {
    FILE *log = fopen("log.txt", "a");
    char timeString[80];
    struct tm* timeInfo = localtime(&block->lastRestartTime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);
    fprintf(log, "%s        %d             %s    %s\n", block->name, block->restartCount, timeString, block->reason);
    printf("%s        %d             %s    %s\n", block->name, block->restartCount, timeString, block->reason);
    fclose(log);
}

void runSwBlock(SwBlock *block) {
    pid_t pid = fork();

    if (pid == 0) {
        srand(time(NULL));
        sleep(rand() % 5);

        if ((rand() % 2) == 0) {
            kill(getpid(), SIGTERM);
        } else {
            exit(0);
        }
    } else {
        printLog(block);
        block->pid = pid;
    }
}

void signalHandler(int signum) {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        SwBlock *block = NULL;

        for (int i = 0; i < swBlockCount; i++) {
            if (blocks[i].pid == pid) {
                block = &blocks[i];
                break;
            }
        }

        if (block) {
            block->restartCount++;
            block->lastRestartTime = time(NULL);
            
            if (WIFEXITED(status)) {
                snprintf(block->reason, sizeof(block->reason), "Exit(%d)", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                int chstatus = WTERMSIG(status);
                snprintf(block->reason, sizeof(block->reason), "Signal(%s)", strsignal(chstatus));
            } else {
                snprintf(block->reason, sizeof(block->reason), "Unknown");
            }

            runSwBlock(block);
        } else {
            printf("자식 프로세스 %d 종료됨.\n", pid);
        }
    }
}

void initSigaction() {
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);

    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, 0) == -1) {
        printf("sigaction");
        exit(1);
    }
}

void trimStr(char *str) {
    char *start = str;
    char *end = str + (strlen(str) - 1);
    while (isspace(*start)) start++;
    while (isspace(*end)) end--;
    memmove(str, start, end - start + 1);
    str[end - start + 1] = '\0';
}

int readSwBlocks(FILE *file) {
    char buf[256];
    int index = 0;

    while (index < MAX_SW_BLOCKS && fgets(buf, sizeof(buf), file)) {
        char* token = strtok(buf, ";");
        trimStr(token);
        strcpy(blocks[index].name, token);
        strcpy(blocks[index].reason, "Init");
        blocks[index].lastRestartTime = time(NULL);

        for (int paramIndex = 0; paramIndex < MAX_PARAMETERS; paramIndex++) {
            token = strtok(NULL, ";");
            if (token) {
                trimStr(token);
                strcpy(blocks[index].parameters[paramIndex], token);
            }
        }
        index++;
    }

    return index;
}

int main() {
    srand(time(NULL));
    initLog();

    FILE *fileList = fopen("swblocks.txt", "r");
    swBlockCount = readSwBlocks(fileList);
    fclose(fileList);

    initSigaction();
    for (int i = 0; i < swBlockCount; i++) {
        runSwBlock(&blocks[i]);
        sleep(1);
    }

    while (1) sleep(1);
}