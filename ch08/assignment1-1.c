#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>

int main() {
  putenv("MYDATA=5");

  execl("assignment1-2", "aggisnment-1-2", (char *)0);
}
