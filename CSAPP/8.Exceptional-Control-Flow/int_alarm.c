#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TIME_LIMIT 5

void catch_int() {
  printf("\nI got you!\n");
  printf("Now we are inside the SIGINT handler\n");
  while (1) {
    sleep(1);
    printf("tick...\n");
  }
}

void handle_alarm() {
  printf("Uh-oh. Time up\n");
  exit(0);
}

int main(int argc, char *argv[])
{
  signal(SIGALRM, handle_alarm);
  signal(SIGINT, catch_int);
  printf("Timer start. Do nothing for now\n");
  alarm(TIME_LIMIT);
  sleep(TIME_LIMIT - 3);
  printf("Now! Click Ctrl-C!\n");
  sleep(10000);
  return 0;
}
