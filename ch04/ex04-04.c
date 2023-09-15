#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  
  char *filename = argv[1];
  if ( access(filename, R_OK) == -1 ) { 
    fprintf( stderr, "User cannot read file %s \n", filename);
    exit(1);
  }
  printf("%s readable, proceeding \n", filename);
}
