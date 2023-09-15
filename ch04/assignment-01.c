#include<stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char* file1 = argv[1];
  char* file2 = argv[2];

  if(symlink(file1, file2)) printf("soft-link failed\n");
  remove(file1);

  if ( access(file2, F_OK) == -1 ) {
    printf("%s is not exists\n", file2);
  } else {
    printf("%s is exists\n", file2);
  }
}
