#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void try() {
  if (fork() != 0) {
    fork();
    printf("Example\n");  /* 2 lines */
    exit(0);
  }
  return;
}
int main(int argc, char *argv[])
{
  try();
  fork();
  printf("Example\n");  /* 2 lines */
  exit(0);
}
