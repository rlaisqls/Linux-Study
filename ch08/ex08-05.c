#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main() {

  pid_t pid;

  if ((pid = fork()) > 0) {
    printf("[ex08-05.c] PPID:%d, PID:%d\n", getppid(), getpid());
    sleep(1);
  } else if (pid == 0) {
    printf("[ex08-05.c] PPID:%d, PID:%d\n", getppid(), getpid());
    execl("ex08-06", "ex08-06", (char *)0);
  } else printf("fail to fork\n");
}
