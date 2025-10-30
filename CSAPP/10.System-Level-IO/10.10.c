#include <fcntl.h>
#include <unistd.h>
#include "rio/rio.h"

#define MAXLINE 128

int main(int argc, char **argv) {
  int n;
  rio_t rio;
  char buf[MAXLINE];

  if (argc >= 2) {
    int fd = open(argv[1], O_RDWR, 0);
    dup2(fd, STDOUT_FILENO);
  }

  rio_readinitb(&rio, STDIN_FILENO);
  while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    rio_writen(STDOUT_FILENO, buf, n);
  }
  return 0;
}
