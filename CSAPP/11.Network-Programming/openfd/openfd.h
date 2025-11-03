#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);
