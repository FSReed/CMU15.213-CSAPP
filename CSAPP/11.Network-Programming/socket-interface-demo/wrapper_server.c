#include "../openfd/openfd.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct sockaddr_storage clientaddr;
  socklen_t clientlen = sizeof(struct sockaddr_storage);
  int connfd;

  int listenfd = open_listenfd("15213");
  if (listenfd < 0) {
    fprintf(stderr, "Failed to open listen fd\n");
    return -1;
  }
  if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen)) < 0) {
    fprintf(stderr, "Failed to accept\n");
    return -1;
  }
  printf("Hello from server\n");
  close(connfd);
  close(listenfd);
  return 0;
}

