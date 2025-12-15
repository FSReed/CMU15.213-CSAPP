#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void try() {
  fork();
  printf("Example\n");
  fork();
  return;
}

int main(int argc, char *argv[]) {
  try(); fork();
  printf("Example\n");
  exit(0);
}
