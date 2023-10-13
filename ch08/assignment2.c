#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<math.h>

int main() {
  pid_t pid1, pid2;
  int status;
  int x, y;

  pid1 = pid2 = -1;
  scanf("%d %d", &x, &y);

  pid1 = fork();
  if (pid1 > 0) pid2 = fork();

  if (pid1 > 0 && pid2 > 0) {
    printf("pps - pid1: %d pid2: %d\n", pid1, pid2);

    waitpid(pid2, &status, 0);
    int pid2res = status>>8;
  
    waitpid(pid1, &status, 0);
    int pid1res = status>>8;

    int parentres = pow(x, y);

    printf("%d - %d - %d = %d", pid2res, pid1res, parentres, pid2res - pid1res - parentres);  

  } else if (pid1 == 0 && pid2 == -1) {
    printf("ps1 - pid1: %d pid2: %d\n", pid1, pid2);
    
    int res = ((y * (y+1))/2) - ((x * (x+1)) / 2) + x; 
    exit(res);

  } else if (pid1 > 0 && pid2 == 0) {
    printf("ps2 - pid1: %d pid2: %d\n", pid1, pid2);
 
    int res = x;
    for (int i = x + 1; i <= y; i++) {
       res *= i;
    }
    exit(res);
 
  } else printf("fail to fork\n");
}
