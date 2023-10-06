#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main() {
  pid_t pid;
  int status;

  pid = fork();
  
  if (pid > 0) {
    printf("parent: waiting..\n");
    wait(&status);
    printf("parent: status is %d\n", status);
  } else if (pid == 0) {
    sleep(1);
    printf("child: bye!\n");
    exit(2);
  } else {
    exit(1);
  }

  printf("bye!\n");
}
