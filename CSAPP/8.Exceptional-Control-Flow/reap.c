#include <asm-generic/errno-base.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void handler1() {
  int old_errno = errno;
  waitpid(-1, NULL, 0);
  write(STDOUT_FILENO, "Reaped\n", 8);
  sleep(1);
  errno = old_errno;
}

void handler2() {
  int old_errno = errno;
  while (waitpid(-1, NULL, 0) > 0) {
    write(STDOUT_FILENO, "Reaped\n", 8);
  }
  if (errno != ECHILD) {
    write(STDOUT_FILENO, "Wrong PID\n", 11);
  }
  sleep(1);
  errno = old_errno;
}

int main(int argc, char *argv[]) {
  char buf[128];

  signal(SIGCHLD, handler2);
  for (int i = 0; i < 3; ++i) {
    if (fork() == 0) {
      printf("Hello from children %d\n", getpid());
      exit(0);
    }
  }
  read(STDIN_FILENO, buf, sizeof(buf));
  printf("Processing\n");
  while (1);
  return 0;
}
