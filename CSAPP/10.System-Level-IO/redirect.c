#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd1 = open(argv[1], O_RDWR, 0);
  /* redirect standard output */
  int new_fd = dup2(fd1, STDOUT_FILENO);
  /* these texts will be printed into file argv[1] */
  printf("New fd is %d\n", new_fd);
  printf("Hello World\n");
  fflush(stdout);

  /* Redirect standard inoput */
  int fd2 = open(argv[1], O_RDONLY, 0);
  dup2(fd2, STDIN_FILENO);

  char buf[256];
  int count = 0;
  /* flush the stdout immediately after each write */
  while (fgets(buf, sizeof(buf), stdin) != NULL) {
    printf("Read %s", buf);
    fflush(stdout);
    if (count >= 10) {
      break;
    }
    ++count;
  }
  return 0;
}
