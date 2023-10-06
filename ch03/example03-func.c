#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void file1(char *filename)
{  
	int fd = open(filename, O_RDWR, 0644);
	if (fd < 0) 
	{	
	   	printf("%s(%d)\n", strerror(errno), errno);
	}
}


void file2(char *filename)
{
	int fd = open(filename, O_RDWR|O_CREAT, 0644);
	char a[1024] = "01234567890123";
	printf("%d\n", (int)write(fd, a, 10));
	printf("%s(%d)\n", strerror(errno), errno);
	close(fd);
}

