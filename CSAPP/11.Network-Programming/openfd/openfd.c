#include "openfd.h"

int open_clientfd(char *hostname, char *port) {
  struct addrinfo hints;
  struct addrinfo *result, *p;
  int clientfd, err_code;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ((err_code = getaddrinfo(hostname, port, &hints, &result)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err_code));
    return -1;
  }

  for (p = result; p; p = p->ai_next) {
    clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (clientfd < 0) {
      continue;
    }
    if (connect(clientfd, p->ai_addr, p->ai_addrlen) == 0) {
      // connected
      break;
    }
    close(clientfd);
  }

  freeaddrinfo(result);
  return !p ? -1 : clientfd;
}

int open_listenfd(char *port) {
  struct addrinfo hints;
  struct addrinfo *result, *p;
  int listenfd, err_code, optval = 1;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_ADDRCONFIG | AI_PASSIVE | AI_NUMERICHOST;

  if ((err_code = getaddrinfo(NULL, port, &hints, &result)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err_code));
    return -1;
  }

  for (p = result; p; p = p->ai_next) {
    listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (listenfd < 0) {
      continue;
    }
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0) {
      fprintf(stderr, "setsockopt failed\n");
      return -1;
    }
    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
      break;
    }
    close(listenfd);
  }

  freeaddrinfo(result);
  if (!p) {
    return -1;
  }

  listen(listenfd, 1024);
  return listenfd;
}
