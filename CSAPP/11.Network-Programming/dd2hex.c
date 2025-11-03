#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  struct in_addr inaddr;
  char buf[64];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [dotted-decimal]\n", argv[0]);
    return -1;
  }

  if (!inet_pton(AF_INET, argv[1], &inaddr.s_addr)) {
    fprintf(stderr, "Wrong dd format\n");
    return -1;
  }

  printf("After pton: %08x\n", inaddr.s_addr);
  int hex = ntohl(inaddr.s_addr);
  printf("After ntoh: %08x\n", hex);

  return 0;
}
