#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv) {
  char buf[64];
  int fd1 = open(argv[1], O_RDWR, 0);
  int fd2 = open(argv[1], O_RDWR, 0);
  int fd3 = open(argv[1], O_RDONLY, 0);
  write (fd1, "Hello   World\n", 13);
  write(fd2, "Goodbye", 7);
  read(fd3, buf, 13);
  close(fd1);
  close(fd2);
  close(fd3);
  printf("%s\n", buf);
  return 0;
}
