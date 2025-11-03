#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
  struct sockaddr_in sockin;
  struct sockaddr_storage client_addr;
  socklen_t client_len = sizeof(struct sockaddr_storage);

  sockin.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &sockin.sin_addr.s_addr);
  sockin.sin_port = htons(15213);

  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (bind(listenfd, (struct sockaddr *)&sockin, sizeof(struct sockaddr_in))) {
    fprintf(stderr, "Failed to bind\n");
  }
  listen(listenfd, 1024);
  int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);
  write(connfd, "I see you\n", 10);

  close(connfd);
  close(listenfd);
  return 0;
}
