#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 512

int main(){
	char msg[SIZE];
	int filedes[2];

	pid_t pid;

	if (pipe(filedes) == -1){
		printf("fail to call pipe()\n");
		exit(1);
	}

	if ((pid = fork()) == -1) {
		printf("fail to call fork()\n");
		exit(1);
	} else if(pid > 0) {
		close(filedes[1]);
		strcpy(msg, "apple is red.\n");
		write(filedes[1], msg, SIZE);
		printf("[parent] %s\n", msg);
	} else {
		close(filedes[0]);
		fork();
		sleep(1);
		read(filedes[0], msg, SIZE);
		printf("[child] %s\n", msg);
	}
}

// 세 개의 프로세스를 생성, 하나의 프로세스에서 두 개의 프로세스로 데이터를 전달