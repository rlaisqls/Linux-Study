#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main() {
  printf("[ex08-06.c] PPID:%d, PID:%d\n", getppid(), getpid());
}
