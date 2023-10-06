#include<unistd.h>

int main() {
  execlp("ls", "ls", "-l", "apple/", (char *)0);
}
