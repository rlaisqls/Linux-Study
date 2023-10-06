#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<math.h>

int main() {
  pid_t pid;
  int status;

  int x, y;
  scanf("%d %d", &x, &y);

  pid = fork();

  if (pid > 0) {
    int res = pow(x, y);
    wait(&status);
    printf("%d + %d = %d", res, (status>>8), res + (status>>8));
  } else if (pid == 0) {
    int res = ((y * (y+1))/2) - ((x * (x+1)) / 2) + x;
    exit(res);
  } else {
    exit(1);
  }
}
