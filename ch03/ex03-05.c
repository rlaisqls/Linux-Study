#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main(int argc, char **argv) {
	int filedes;
	off_t newpos;

	filedes = open(argv[1], O_RDONLY);

	// rw pointer을 EOF로 이동
	newpos = lseek(filedes, (off_t)0, SEEK_END);
	printf("file size : %lld\n", newpos);

	close(filedes);
}
