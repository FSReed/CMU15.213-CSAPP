#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int mysystem(char *command) {
  pid_t pid;
  int status;

  if (fork() == 0) {
    char *argv[4] = {"", "-c", command, NULL};
    execve("/bin/sh", argv, __environ);
  }

  waitpid(-1, &status, 0);

  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  } else {
    /* sh is interrupted by a signal */
    printf("By Signal\n");
    return WTERMSIG(status);
  }
}

int main(int argc, char *argv[])
{
  int status = mysystem("./exit_8");
  printf("Exit status: %d\n", status);
  exit(0);
}
