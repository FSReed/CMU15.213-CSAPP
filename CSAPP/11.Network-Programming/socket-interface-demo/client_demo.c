#include "../openfd/openfd.h"
#include "../../10.System-Level-IO/rio/rio.h"

int main(int argc, char *argv[]) {
  const int MAXLINE = 64;
  char buf[MAXLINE];
  int clientfd, n;
  rio_t in_rio, rio;

  clientfd = open_clientfd("127.0.0.1", "15213");
  if (clientfd < 0) {
    fprintf(stderr, "Failed to connect to server\n");
    return -1;
  }
  printf("Connected.\n");

  rio_readinitb(&in_rio, STDIN_FILENO);
  rio_readinitb(&rio, clientfd);
  while ((n = rio_readlineb(&in_rio, buf, MAXLINE)) != 0) {
    rio_writen(clientfd, buf, n);
    n = rio_readlineb(&rio, buf, MAXLINE);
    write(STDOUT_FILENO, buf, n);
  }
  close(clientfd);
  return 0;
}
