#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {
  int i = 1;
  pid_t pid = fork();
  
  if (pid > 0) {
    printf("p %d\n", ++i);
  } else {
    printf("c %d\n", --i);
  }
}
