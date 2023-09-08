#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
        char pathname[] = "temp.txt";
        if (open(pathname, O_RDWR|O_CREAT|O_EXCL, 0644) == -1) {
                printf("file open error");
                exit(1);
        }
}
