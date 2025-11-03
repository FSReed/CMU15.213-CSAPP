#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  struct addrinfo hint;
  struct addrinfo *result;
  struct sockaddr_storage client_addr;
  socklen_t clientlen = sizeof(struct sockaddr_storage);

  // Initialize the hint
  memset(&hint, 0, sizeof(struct addrinfo));
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_flags = AI_PASSIVE;

  int err_code = getaddrinfo("127.0.0.1", "15213", &hint, &result);
  if (err_code != 0) {
    fprintf(stderr, "%s\n", gai_strerror(err_code));
  }
  int listenfd = socket(result->ai_family, result->ai_socktype, 0);
  if (bind(listenfd, result->ai_addr, result->ai_addrlen)) {
    fprintf(stderr, "Failed to bind\n");
    return -1;
  }
  listen(listenfd, 1024);
  int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &clientlen);
  printf("Hello from server\n");

  freeaddrinfo(result);
  close(connfd);
  close(listenfd);
  return 0;
}
