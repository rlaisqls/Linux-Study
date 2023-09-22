#include<stdio.h>
#include<math.h>
#include<sys/types.h>
#include<unistd.h>

int i = 1;

int main() {
  //int i = 1;
  
  int n;
  scanf("%d", &n);
  
  pid_t pid = fork();

  if (pid > 0) {
    int res = n;
    for (int j = n-1; j>=1; j--) {
      res += j;
    }
    printf("p %d\n", res);
    printf("p %p\n", &i);
  } else {
    int res = n;
    for (int j = n-1; j>=1; j--) { 
      res *= j;
    }
    printf("c %d\n", res);
    printf("c %p\n", &i);
  }
  return 0;
}
