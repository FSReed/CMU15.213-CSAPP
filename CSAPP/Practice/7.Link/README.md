# NOTE

## Creating a Static Library

Source code: `addvec.c` and `multvec.c`
Tool: `gcc -c` and `ar`

```C
gcc -c addvec.c multvec.c
ar rcs libvector.a addvec.o multvec.o
```

