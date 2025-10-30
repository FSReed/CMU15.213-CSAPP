#include <sys/types.h>

#define RIO_BUFSIZE 8192

typedef struct {
  int rio_fd;
  int rio_cnt;
  char *rio_bufptr;
  char rio_buf[RIO_BUFSIZE];
} rio_t;

/* ------------------------------------------------
 * Unbuffered r/w
 */

/* Can return short count */
ssize_t rio_readn(int fd, void *usrbuf, size_t n);

/* Never returns a short count */
ssize_t rio_writen(int fd, void *usrbuf, size_t n);

/* ------------------------------------------------
 * Buffered read
 */

/* initialize a buffer for a file descriptor */
void rio_readinitb(rio_t *rp, int fd);

/* Read n bytes from the file */
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);

/* Read a line from the file (no more than maxlen - 1 bytes) */
/* NOTE: The last character will be NULL character */
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);
