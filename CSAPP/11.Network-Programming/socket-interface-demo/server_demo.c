#include "../openfd/openfd.h"
#include "../../10.System-Level-IO/rio/rio.h"

int main(int argc, char *argv[]) {
  const int MAXLINE = 64;
  char buf[MAXLINE];
  int listenfd, connfd, n;
  rio_t rio;
  struct sockaddr_storage clientaddr;
  socklen_t clientlen;
  char clientname[MAXLINE], clientport[MAXLINE];

  listenfd = open_listenfd("15213");
  if (listenfd < 0) {
    fprintf(stderr, "Failed to get the server's listenfd\n");
    return -1;
  }

  // Iterative server
  while (1) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
    if (connfd < 0) {
      fprintf(stderr, "Failed to accept a connection\n");
      return -1;
    }
    getnameinfo((struct sockaddr *)&clientaddr, clientlen, clientname, MAXLINE, clientport, MAXLINE, 0);
    printf("Connected to (%s: %s)\n", clientname, clientport);

    rio_readinitb(&rio, connfd);
    while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
      printf("Received %d bytes\n", n);
      rio_writen(connfd, buf, n);
    }
    printf("Tear down the connection...\n");
    close(connfd);
  }

  close(listenfd);
  return 0;
}
