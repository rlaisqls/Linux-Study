#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid > 0) {
        exit(0);
    }

    if (setsid() < 0) {
        perror("setsid failed");
        exit(1);
    }

    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int log_fd = open("/var/log/curtime.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (log_fd < 0) {
        perror("open log file failed");
        exit(1);
    }

    while (1) {
        time_t current_time;
        struct tm* time_info;
        char time_str[80];

        time(&current_time);
        time_info = localtime(&current_time);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S\n", time_info);

        write(log_fd, time_str, strlen(time_str));

        sleep(10);
    }

    close(log_fd);

    return 0;
}

