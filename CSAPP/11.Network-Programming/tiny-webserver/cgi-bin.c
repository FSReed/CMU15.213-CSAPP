#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
  char *args = getenv("QUERY_STRING");
  char *p = strstr(args, "&");
  if (!p) {
    printf("Need 2 arguments\n");
    return -1;
  }

  *p = '\0';
  int arg1 = atoi(args);
  int arg2 = atoi(p + 1);
  printf("Answer: %d\n", arg1 + arg2);
  return 0;
}
