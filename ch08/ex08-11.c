#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>

int main() {
  printf("%s\n", getenv("APPLE"));
  unsetenv("APPLE");

  if(!getenv("APPLE")) {
    printf("APPLE not found\n");
  }
}
