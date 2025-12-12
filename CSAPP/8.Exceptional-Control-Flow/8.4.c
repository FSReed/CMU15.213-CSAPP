#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int status;
  pid_t pid;

  printf("Start\n");  // parent: +1
  pid = fork();
  printf("%d\n", !pid); // child + parent: +2
  if (pid == 0) {
    printf("Child\n");  // child: +1
  } else if (waitpid(-1, &status, 0) > 0 &&
             WIFEXITED(status) != 0) {
    printf("%d\n", WEXITSTATUS(status));  // parent: +1
  }
  printf("Stop\n"); // child + parent: +2

  /** One possible ordering:
   * Start
   * 0
   * 1
   * Child
   * Stop
   * 0
   * Stop
   */
  return 0;
}
