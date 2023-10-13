#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main() {
  pid_t pid;
  int status = 0;

  if ((pid = fork()) > 0) {
     while(!waitpid(pid, &status, WNOHANG)) {
       printf("parent: %d\n", status++);
       sleep(1);
     }
     printf("parent: child - exit(%d)\n", status);
  } else if (pid == 0) {
    sleep(5);
    printf("bye!\n");
    exit(0);
  } else printf("fail to fork\n");
}
