#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<time.h>

int num = 0;

int main() {

  static struct sigaction act;

  void int_handle(int);
  act.sa_handler = int_handle;
  sigfillset(&(act.sa_mask));
  sigaction(SIGINT, &act, NULL);

  while(1) {
    printf("I'm sleepy..\n");
    sleep(1);
    if (num >= 5) exit(0);
  }
}

void int_handle(int signum) {

  int log_fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
  
  time_t current_time;
  struct tm* time_info;
  char time_str[200];

  time(&current_time);
  time_info = localtime(&current_time);
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S\n", time_info);

  strcat(time_str, ": SIGINT occured");
  printf("%s\n", time_str);

  write(log_fd, time_str, strlen(time_str));
}
