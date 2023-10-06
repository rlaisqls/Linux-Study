#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

int main() {
  pid_t pid;
  printf("hello!\n");
  pid = fork();
  if (pid > 0) {
    printf("parent\n");
    // sleep을 줘서 자식의 종료를 기다리지 않으면 자식이 좀비가 됨
    // sleep(1);
  } else if (pid == 0) {
    printf("child\n");
    execl("/bin/ls", "ls", "-l", (char*) 0);
    printf("fail to execute ls\n");
  } else {
    printf("parent : fail to fork\n");
  }
  printf("bye!\n");  
}
