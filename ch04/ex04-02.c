#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main() {
  mode_t oldmask = umask(023);
  int fd = open("test.txt", O_CREAT, 0777);
  close(fd);
}
