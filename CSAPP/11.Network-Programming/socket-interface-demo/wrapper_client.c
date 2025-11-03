#include "../openfd/openfd.h"

int main(int argc, char *argv[]) {
  int clientfd = open_clientfd("127.0.0.1", "15213");
  if (clientfd < 0) {
    fprintf(stderr, "Failed to open client fd\n");
    return -1;
  }
  printf("Connected to client fd: %d\n", clientfd);
  return 0;
}

