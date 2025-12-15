#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int a = 5;
  if (fork() != 0) {
    printf("a=%d\n", --a);
  }
  printf("a=%d\n", ++a);
  exit(0);
}
