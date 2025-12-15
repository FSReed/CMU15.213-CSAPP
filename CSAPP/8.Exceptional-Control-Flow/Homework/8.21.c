#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  printf("p");
  fflush(stdout);
  if (fork() != 0) {
    printf("q");
    fflush(stdout);
    return 0;
  } else {
    printf("r");
    fflush(stdout);
    waitpid(-1, NULL, 0);
  }
  return 0;
}
