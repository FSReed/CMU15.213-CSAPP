#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

jmp_buf env;

void handler() {
  longjmp(env, 1);
}

char *tfgets(char *buf, int n, FILE *restrict stream) {
  switch (setjmp(env)) {
  case 0:
    signal(SIGALRM, handler);
    alarm(5);
    fgets(buf, sizeof(buf), stream);
    return buf;
  case 1:
    return NULL;
  default:
    printf("No way\n");
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  char buf[32];

  char *result = tfgets(buf, sizeof(buf), stdin);
  if (result != NULL) {
    printf("%s", result);
  } else {
    printf("Timeout!\n");
  }
  exit(0);
}
