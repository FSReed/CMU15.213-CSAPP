#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
  struct sockaddr_in sockin;
  sockin.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &sockin.sin_addr.s_addr);
  sockin.sin_port = htons(15213);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (connect(sockfd, (struct sockaddr *)&sockin, sizeof(struct sockaddr_in))) {
    fprintf(stderr, "Failed to connect\n");
    return -1;
  }
  printf("Connected\n");

  char buf[10];
  read(sockfd, buf, 10);
  printf("From server: %s", buf);
  return 0;
}
