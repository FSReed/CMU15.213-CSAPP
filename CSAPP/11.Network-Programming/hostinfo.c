#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

/* similar to `nslookup` */
int main(int argc, char *argv[]) {
  struct addrinfo hints;
  struct addrinfo *result, *p;
  char buf[64];

  if (argc != 2) {
    fprintf(stderr, "Usage: hostinfo [website]\n");
    return -1;
  }

  // initialize hints
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  int err_code = getaddrinfo(argv[1], NULL, &hints, &result);
  if (err_code != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err_code));
    return -1;
  }

  int flags = NI_NUMERICHOST;
  for (p = result; p; p = p->ai_next) {
    getnameinfo(p->ai_addr, p->ai_addrlen, buf, 64, NULL, 0, flags);
    // Problem 11.7: using inet_ntop
    /* struct sockaddr_in *sockp = (struct sockaddr_in *)p->ai_addr; */
    /* inet_ntop(p->ai_family, &sockp->sin_addr, buf, 64); */
    printf("%s\n", buf);
  }

  freeaddrinfo(result);
  return 0;
}
