#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

void onerror(char *msg) {
	printf("%s", msg);
	exit(1);
}

int main() {
	int p1[2];
	int i;
	pid_t pid1;
	fd_set initset, newset;

	pid1 = 0;

	if(pipe(p1) == -1)
		onerror("fail to call pipe() #1\n");
	if((pid1 = fork()) == -1)
		onerror("fail to call fork() #1\n");

	if (pid1 > 0) {
		printf("parent: %d\n", getpid());
		close(p1[0]); 

        int fd_read = open("file.txt", O_RDONLY);
        char* buffer = (char*) malloc(fpathconf(p1[1], _PC_PIPE_BUF));

        ssize_t bytesRead;
        while ((bytesRead = read(fd_read, buffer, sizeof(buffer))) > 0) {
            write(p1[1], buffer, bytesRead);
        }
        close(fd_read);
        free(buffer);
	} else if (pid1 == 0) {
		printf("child1: %d\n", getpid());

		close(p1[1]);

        int fd_write = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        char* buffer = (char*) malloc(fpathconf(p1[1], _PC_PIPE_BUF));

		FD_ZERO(&initset);
		FD_SET(p1[0], &initset);

		newset = initset;
		while (select(p1[0] + 1, &newset, NULL, NULL, NULL) > 0) {
			if (FD_ISSET(p1[0], &newset)) {
				if (read(p1[0], buffer, sizeof(buffer)) > 0) {
                    write(fd_write, buffer, bytesRead);
                }
            }
			newset = initset;
		}

		printf("child1: bye!\n");
        close(fd_write);
        free(buffer);
		exit(0);
	}
}