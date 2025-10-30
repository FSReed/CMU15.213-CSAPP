# Homework Problems

## 10.6

Source code: `10.6.c`. The answer is `fd2 = 4`

## 10.7

Change `buf[MAXLINE] to buf[RIO_BUFSIZE]`.

## 10.8 & 10.9

Source code: `fstatcheck.c`

## 10.10

Source code: `10.10.c`

- Don't change existing code in `rio/rio_demo.c`, only insert code. Notice `rio_demo.c` writes to `STDOUT_FILENO` in the loop, so if a target file is provided, we need to redirect `stdout` to the target file.

