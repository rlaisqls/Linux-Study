#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
	char* msg[3] = {"Apple is red\n", "Banana is yellow\n", "Cherry is red\n"};
	int p[2];
	pid_t pid;
	int cnt;

	if (pipe(p) == -1) {
		printf("fail to call pipe()\n");
		exit(1);
	}

	if ((pid = fork()) == -1) {
		printf("fail to call fork()\n");
		exit(1);
	} else if (pid > 0) {
		printf("[patent]\n");
		close(p[0]);
		for (cnt = 0; cnt < 3; cnt++) {
			write(p[1], msg[cnt], strlen(msg[cnt] + 1));
		}
	} else {
		printf("[child]\n");
		close(p[1]);

		// 자식 프로세스는 표준 출력을 읽기용 파이프의 사본으로 만든 후에 wc를 실행하고,
		// wc는 실행되면서 표준 출력에서 무언가를 읽으려고 한다.
		dup2(p[0], 0);
		execlp("wc", "wc", (char*)0);
		printf("[child] fail to call execlp()\n");
	}
}
