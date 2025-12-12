#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void catch(int sig_num) {
  printf("\nCannot kill me XD\n");
  sleep(2);
  printf("Ok, fine...\n");
  printf("[sig_num: %d]\n", sig_num);
  kill(0, SIGKILL);
}

int main(int argc, char *argv[]) {
  signal(SIGINT, catch);
  while (1) {}
  return 0;
}
