#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  struct stat st;
  int fd = -1;
  char *type, *readok;

  if (argc >= 2) {
    fd = atoi(argv[1]);
  }

  /* Shell should redirect 3 to stdin on fork() */
  dup2(STDIN_FILENO, fd);

  if (fstat(fd, &st) != 0) {
    printf("Error parsing the file metadata\n");
    return -1;
  }

  if (S_ISREG(st.st_mode)) {
    type = "regular";
  } else if (S_ISDIR(st.st_mode)) {
    type = "directory";
  } else if (S_ISSOCK(st.st_mode)) {
    type = "socket";
  } else {
    type = "other";
  }

  if ((st.st_mode & S_IRUSR)) {
    readok = "yes";
  } else {
    readok = "no";
  }

  printf("type: %s, read: %s\n", type, readok);
  return 0;
}
