#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
  char content[64];
  char *args = getenv("QUERY_STRING");
  char *p = strstr(args, "&");
  if (!p) {
    printf("Need 2 arguments\n");
    return -1;
  }
  int arg1 = 0, arg2 = 0;
  sscanf(args, "first=%d&second=%d", &arg1, &arg2);
  sprintf(content, "Answer: %d + %d = %d\r\n", arg1, arg2, arg1 + arg2);

  printf("Connection close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n");
  printf("\r\n");

  printf("%s", content);
  fflush(stdout);
  return 0;
}
