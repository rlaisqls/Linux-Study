#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
	char buffer[1];
	int fd = open("temp1.txt", O_RDWR);
	int count = 0;

    	while (read(fd, buffer, sizeof(buffer)) > 0) {
                char* b = &buffer[0];
		if('a' <= *b && *b <= 'z') {
			*b = *b - 'a' + 'A';			
            		lseek(fd, -1, SEEK_CUR); 
            		if (write(fd, b, 1) < 1) {
				break;
			}
			count++;
                }
                else if ('A' <= *b && *b <= 'Z') {
                        count++;
                }
		printf("%c", *b);
  	}

        close(fd);
	printf("\nalphabet count: %d", count);
}
