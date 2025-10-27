# NOTE

## Creating a Static Library

Source code: `addvec.c` and `multvec.c`
Tool: `gcc -c` and `ar`

```shell
gcc -c addvec.c multvec.c
ar rcs libvector.a addvec.o multvec.o
```

## Creating a Dynamic Library

```shell
gcc -shared -fpic -o libvector.so addvec.o multvec.o
```

## Library Inter-Positioning

The dynamic linker will first search in libraries provided by the `LD_PRELOAD` environment variable before any other shared libraries when it resolves the undefined references. This mechanism only requires an executable object file.  
In `bash`, we can run programs with `LD_PRELOAD` defined as custom dynamic libraries:

```bash
# See this example in Library_Interpositioning/ folder
LD_PRELOAD="./mymalloc_runtime.so" /usr/bin/uptime
```

