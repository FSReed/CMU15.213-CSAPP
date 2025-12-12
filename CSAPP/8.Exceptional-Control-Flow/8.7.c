#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void catch_int(int sig_num) {
}

int main(int argc, char *argv[]) {
  signal(SIGINT, catch_int);
  int time = atoi(argv[1]);

  int rem_time = sleep(time);
  printf("Slept for %d of %d seconds\n", time - rem_time, time);
  return 0;
}
