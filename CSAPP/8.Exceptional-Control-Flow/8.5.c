#include <unistd.h>
#include <stdio.h>

unsigned int wakeup(unsigned int sec) {
  int time = sleep(sec);
  return sec - time;
}

int main() {
  printf("wakeup after %d seconds\n", wakeup(4));
  return 0;
}

