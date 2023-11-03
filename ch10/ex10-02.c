#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  sigset_t set;
  int res;

  sigemptyset(&set);
  res = sigismember(&set, SIGALRM);
  printf("SIGALRM is %s a member\n", res ? "" : "not");
  
  sigaddset(&set, SIGALRM);
  res = sigismember(&set, SIGALRM);
  printf("SIGALRM is %s a member\n", res ? "" : "not");
  
  sigfillset(&set);
  res = sigismember(&set, SIGCHLD);
  printf("SIGCHLD is %s a member\n", res ? "" : "not");

  res = sigismember(&set, SIGALRM);
  printf("SIGALRM is %s a member\n", res ? "" : "not");

  sigdelset(&set, SIGCHLD);
  res = sigismember(&set, SIGCHLD);
  printf("SIGCHLD is %s a member\n", res ? "" : "not");
}
