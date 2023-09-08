#include<stdio.h>

int sumtest() {
  int sum=0;
  for (int i=1; i<=100; i++) {
    sum += i;
  }
  printf("%d", sum);
  return 0;
}
