#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
  if (fork() == 0) {
    printf("9");
    fflush(stdout);
  } else {
    printf("0");
    fflush(stdout);
    waitpid(-1, NULL, 0);
  }
  printf("3");
  fflush(stdout);
  printf("6");
  exit(0);
  /** Child: 936(exit)
   * Parent: 0(wait)36(exit)
   * ------------------------> 4 different positions for 0
   *
   * 093636
   * 903636
   * 930636
   * 936036
   */
}
