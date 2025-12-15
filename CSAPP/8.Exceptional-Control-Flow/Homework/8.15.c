#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void try() {
  if (fork() == 0) {
    fork();
    fork();
    printf("Example\n");  /* 2 lines */
    return;
  }
  return;
}
int main(int argc, char *argv[])
{
  try();
  printf("Example\n");  /* 2 lines */
  exit(0);
}
