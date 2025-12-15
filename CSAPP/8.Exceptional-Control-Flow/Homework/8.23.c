#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int counter = 0;

void handler(int sig) {
  counter++;
  sleep(1);
  return;
}

int main(int argc, char *argv[]) {
  int i;
  signal(SIGUSR2, handler);

  if (fork() == 0) {
    for (int i = 0; i < 5; ++i) {
      kill(getppid(), SIGUSR2);
      printf("SIGUSR2 Sent to Parent\n");
    }
    exit(0);
  }

  wait(0);
  printf("counter = %d\n", counter);
  exit(0);
}
