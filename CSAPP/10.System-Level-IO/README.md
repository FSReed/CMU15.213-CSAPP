# Notes

## Sharing Files (with child process)

> Source code: `child_share.c`

Although `fork` copies the file descriptor table, **each underlying file offset** is shared between parent and child.  
In `child_share.c`, if the given file contains `"foobar"`, the output will be `o` instead of `f`.

