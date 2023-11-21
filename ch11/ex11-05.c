#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512

int main() {
    int filedes[2];

    if (pipe(filedes) == -1) {
        printf("fail to call pipe()\n");
        exit(1);
    }
    
    int pid = fork();
    if (pid == -1) {
        /* fork() 호출 실패 */
    } else if (pid > 0) {
        close(filedes[0]);
        /* filedes[1]을 지정하여 파이프에 메시지 쓰기 */
    } else {
        close(filedes[1]);
        /* filedes[0]을 지정하여 파이프로부터 메시지 읽기*/
    }
}