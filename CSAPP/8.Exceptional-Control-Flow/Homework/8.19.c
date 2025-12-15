#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n = 6;
  for (int i = n - 1; i >= 0; i -= 2) {
    fork();
  }
  printf("Hello\n");
  exit(0);
}
