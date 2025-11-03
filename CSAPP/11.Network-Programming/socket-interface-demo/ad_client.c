#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  struct addrinfo hint;
  struct addrinfo *result, *p;

  // Initialize the hint
  memset(&hint, 0, sizeof(struct addrinfo));
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;

  int err_code = getaddrinfo("127.0.0.1", "15213", &hint, &result);
  if (err_code != 0) {
    fprintf(stderr, "error: %s\n", gai_strerror(err_code));
  }

  // Try every entry in the list
  int clientfd = -1;
  for (p = result; p; p = p->ai_next) {
    clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (connect(clientfd, p->ai_addr, p->ai_addrlen)) {
      fprintf(stderr, "Failed to connect\n");
      close(clientfd);
      continue;
    }
    printf("Client connected\n");
    break;
  }
  if (clientfd == -1) {
    fprintf(stderr, "Failed to connect\n");
    return -1;
  }

  close(clientfd);
  freeaddrinfo(result);
  return 0;
}
