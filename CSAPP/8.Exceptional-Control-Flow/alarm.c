#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define TIME_LIMIT 5
#define CONNECT_TIME 6

void handle_alarm() {
  printf("Reach time limit!\n");
  /* kill(0, SIGKILL); */
}

int main(int argc, char *argv[])
{
  signal(SIGALRM, handle_alarm);
  printf("Start to connect...\n");
  alarm(TIME_LIMIT);
  for (int i = 0; i < CONNECT_TIME; ++i) {
    sleep(1);
    printf("%d seconds passed...\n", i + 1);
  }
  printf("Connected\n");
  int rem_time = alarm(0);
  printf("Remaining time: %d seconds\n", rem_time);
  return 0;
}
