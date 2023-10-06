#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int filedes;

void closeFile() {
  printf("closeFile %d", filedes);
  close(filedes);
}

int main(int argc, char **argv) {

        atexit(closeFile);
	off_t newpos;
	filedes = open(argv[1], O_RDONLY);

	newpos = lseek(filedes, (off_t)0, SEEK_END);
	printf("file size : %lld\n", newpos);
}
