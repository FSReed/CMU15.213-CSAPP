#include "../../10.System-Level-IO/rio/rio.h"
#include "../openfd/openfd.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAXLINE 256

void doit(int connfd);
void clienterror(int connfd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void read_requesthdrs(rio_t *rio);
int parse_uri(char *uri, char *filename, char *cgi_args);
void serve_static(int connfd, char *filename, int filesz);
void serve_dynamic(int connfd, char *filename, char *cgi_args);
void getfiletype(char *filename, char *filetype);

int main(int argc, char *argv[]) {
  int listenfd, connfd, n;
  struct sockaddr_storage clientaddr;
  socklen_t clientlen;
  char clientname[MAXLINE], clientport[MAXLINE];

  listenfd = open_listenfd("15213");
  if (listenfd < 0) {
    fprintf(stderr, "Failed to get the server's listenfd\n");
    return -1;
  }

  // Iterative server
  while (1) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
    if (connfd < 0) {
      fprintf(stderr, "Failed to accept a connection\n");
      return -1;
    }
    getnameinfo((struct sockaddr *)&clientaddr, clientlen, clientname, MAXLINE,
                clientport, MAXLINE, 0);
    printf("Connected to (%s: %s)\n", clientname, clientport);
    doit(connfd);
    close(connfd);
  }

  close(listenfd);
  return 0;
}

/* handle one HTTP transaction */
void doit(int connfd) {
  rio_t rio;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char filename[MAXLINE], cgi_args[MAXLINE];
  struct stat sbuf;

  rio_readinitb(&rio, connfd);
  rio_readlineb(&rio, buf, MAXLINE);
  printf("Request headers: \n");
  printf("%s", buf);
  sscanf(buf, "%s %s %s", method, uri, version);
  if (strcasecmp(method, "GET") != 0) {
    clienterror(connfd, method, "503", "Not implemented", "Un-supported method");
    return;
  }
  read_requesthdrs(&rio);

  int is_static = parse_uri(uri, filename, cgi_args);
  if (stat(filename, &sbuf) < 0) {
    clienterror(connfd, filename, "403", "Forbidden", "Cannot access file");
    return;
  }
  if (is_static) {
    serve_static(connfd, filename, sbuf.st_size);
  } else {
    serve_dynamic(connfd, filename, cgi_args);
  }
  return;
}

/* client error */
/* I only handle the case where the static content doesn't exist */
void clienterror(int connfd, char *cause, char *errnum, char *shortmsg, char *longmsg) {
  char buf[MAXLINE], body[MAXLINE];

  /* Print the HTTP response */
  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum,
                                        shortmsg);
  rio_writen(connfd, buf, strlen(buf));
  sprintf(buf, "Content-type: text/html\r\n");
  rio_writen(connfd, buf, strlen(buf));
  sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
  rio_writen(connfd, buf, strlen(buf));

  // Write the body
  sprintf(body, "<html><title>Tiny Error</title>");
  rio_writen(connfd, body, strlen(body));
  sprintf(body, "<body bgcolor=" "ffffff" ">\r\n");
  rio_writen(connfd, body, strlen(body));
  sprintf(body, "%s: %s\r\n", errnum, shortmsg);
  rio_writen(connfd, body, strlen(body));
  sprintf(body, "<p>%s: %s\r\n", longmsg, cause);
  rio_writen(connfd, body, strlen(body));
  sprintf(body, "<hr><em>The Tiny Web server</em>\r\n");
  rio_writen(connfd, body, strlen(body));
}

void read_requesthdrs(rio_t *rio) {}

/* parse the uri */
int parse_uri(char *uri, char *filename, char *cgi_args) {
  char *ptr;

  if (strstr(uri, "cgi-bin") == NULL) {
    printf("Static\n");
    strcpy(cgi_args, "");
    strcpy(filename, ".");
    strcat(filename, uri);
    if (uri[strlen(uri) - 1] == '/') {
      // default page
      strcat(filename, "home.html");
    }
    return 1;
  }

  printf("Dynamic\n");
  ptr = index(uri, '?');
  if (ptr) {
    strcpy(cgi_args, ptr + 1);
    *ptr = '\0';
  } else {
    strcpy(cgi_args, "");
  }
  strcpy(filename, ".");
  strcat(filename, uri);
  return 0;
}

/* serve static content */
/* this function only serves the first line of a static file */
void serve_static(int connfd, char *filename, int filesz) {
  char filetype[32], buf[MAXLINE];
  int n;

  getfiletype(filename, filetype);
  sprintf(buf, "HTTP/1.1 200 OK\r\n");
  rio_writen(connfd, buf, strlen(buf));
  sprintf(buf, "Server: Tiny Web Server\r\n");
  rio_writen(connfd, buf, strlen(buf));
  sprintf(buf, "Connection closed\r\n");
  rio_writen(connfd, buf, strlen(buf));
  sprintf(buf, "Content-type: %s\r\n", filetype);
  rio_writen(connfd, buf, strlen(buf));
  sprintf(buf, "Content-length: %d\r\n", filesz);
  rio_writen(connfd, buf, strlen(buf));
  /* the end of the header */
  sprintf(buf, "\r\n");
  rio_writen(connfd, buf, strlen(buf));

  int filefd = open(filename, O_RDONLY, 0);
  /* char *filep = mmap(0, filesz, PROT_READ, MAP_PRIVATE, filefd, 0); */
  /* close(filefd); */
  /* rio_writen(connfd, filep, filesz); */
  /* munmap(filep, filesz); */

  /* Homework 11.9 */
  char *memfile = (char *)malloc(filesz);
  rio_readn(filefd, memfile, filesz);
  rio_writen(connfd, memfile, filesz);
  close(filefd);
}

/* a simple adder */
void serve_dynamic(int connfd, char *filename, char *cgi_args) {
  char buf[MAXLINE];
  char *emptylist[] = {NULL};

  sprintf(buf, "HTTP/1.1 200 OK\r\n");
  rio_writen(connfd, buf, strlen(buf));
  sprintf(buf, "Server: Tiny Web Server\r\n");
  rio_writen(connfd, buf, strlen(buf));
  /* the end of the header */
  sprintf(buf, "\r\n");
  rio_writen(connfd, buf, strlen(buf));

  sprintf(buf, "Dynamic service with args: %s\r\n", cgi_args);
  rio_writen(connfd, buf, strlen(buf));

  if (fork() == 0) {
    setenv("QUERY_STRING", cgi_args, 1);
    dup2(connfd, STDOUT_FILENO);
    execve(filename, emptylist, __environ);
  }
  wait(NULL);
}

void getfiletype(char *filename, char *filetype) {
  if (strstr(filename, ".html"))
    strcpy(filetype, "text/html");
  else if (strstr(filename, ".gif"))
    strcpy(filetype, "image/gif");
  else if (strstr(filename, ".png"))
    strcpy(filetype, "image/png");
  else if (strstr(filename, ".jpg"))
    strcpy(filetype, "image/jpeg");
  /* Homework 11.7 */
  else if (strstr(filename, ".mp4"))
    strcpy(filetype, "video/mpeg4");
  else
    strcpy(filetype, "text/plain");
}
