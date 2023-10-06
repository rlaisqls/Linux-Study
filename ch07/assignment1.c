#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

int main(int argc, char *argv[]) {

  for (int i=0; i<argc; i++) {
    pid_t pid;
    pid = fork();
    if (pid > 0) {
      //printf("parent %s\n", argv[i]);
      sleep(1);
    } else if (pid == 0) {
      //printf("child %s\n", argv[i]);
      execl("/usr/bin/wc", "wc", argv[i], (char*) 0);
      //printf("failed to run wc command %s\n", argv[i]);
    }
  }
}
