#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
        char pathname[] = "temp0.txt";
        int fd = open(pathname, O_RDWR|O_CREAT|O_EXCL, 0644)
        close(fd);
}
