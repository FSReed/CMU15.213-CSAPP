#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 2

int main(int argc, char *argv[]) {
  int status, i;
  pid_t pid;

  for (i = 0; i < N; ++i) {
    if ((pid = fork()) == 0) {
      /* write to read-only regions */
      int *mem = (int *)0x400000;
      *mem = 40;
      exit(0);
    }
  }

  while ((pid = waitpid(-1, &status, 0)) > 0) {
    if (WIFEXITED(status)) {
      printf("child %d terminated normally with exit status = %d\n", pid, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      /* char buf[64]; */
      /* snprintf(buf, sizeof(buf), "child %d terminated by signal %d", pid, WTERMSIG(status)); */
      /* psignal(WTERMSIG(status), buf); */

      // "Modern" approach, using strsignal()
      int sig_num = WTERMSIG(status);
      fprintf(stderr, "child %d terminated by signal %d: %s\n", pid, sig_num, strsignal(sig_num));
    } else {
      printf("child %d terminated abnormally\n", pid);
    }
  }

  if (errno != ECHILD) {
    fprintf(stderr, "waitpid error\n");
  }

  exit(0);
}
