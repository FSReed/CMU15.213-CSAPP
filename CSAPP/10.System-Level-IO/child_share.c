#include <stdlib.h>
#include <threads.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  int fd = open(argv[1], O_RDONLY, 0);
  char c;

  if (fork() == 0) {
    read(fd, &c, 1);
    exit(0);
  }
  wait(NULL);
  read(fd, &c, 1);
  printf("c = %c\n", c);
  return 0;
}
