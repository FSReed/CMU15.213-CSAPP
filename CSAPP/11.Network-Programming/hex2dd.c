#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
  struct in_addr inaddr;
  int host_order;
  char buf[64];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [hex]\n", argv[0]);
    return -1;
  }

  sscanf(argv[1], "%x", &host_order);
  inaddr.s_addr = htonl(host_order);
  printf("After htonl: 0x%08x\n", inaddr.s_addr);

  if (!inet_ntop(AF_INET, &inaddr, buf, 64)) {
    return -1;
  }

  printf("After ntop: %s\n", buf);

  int hex;
  inet_pton(AF_INET, buf, &hex);
  printf("Hex provided by pton: 0x%08x\n", hex);
  return 0;
}
