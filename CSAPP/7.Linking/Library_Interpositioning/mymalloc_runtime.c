#ifdef RUNTIME

#define _GNU_SOURCE
#include <dlfcn.h> /* malloc wrapper function */
#include <stdio.h>
#include <stdlib.h>

void *malloc(size_t size) {
  void *(*mallocp)(size_t size);
  char *error;

  mallocp = dlsym(RTLD_NEXT, "malloc"); /* Get address of libc malloc */
  if ((error = dlerror()) != NULL) {
    fputs(error, stderr);
    exit(1);
  }

  char *ptr = mallocp(size); /* Call libc malloc */
  /* Cannot use printf here. printf calls malloc, which will cause infinite recursion */
  fprintf(stderr, "malloc(%d) = %p\n", (int)size, ptr);
  return ptr;
}

/* free wrapper function */
void free(void *ptr) {
  void (*freep)(void *) = NULL;
  char *error;

  if (!ptr)
    return;
  freep = dlsym(RTLD_NEXT, "free"); /* Get address of libc free */
  if ((error = dlerror()) != NULL) {
    fputs(error, stderr);
    exit(1);
  }
  freep(ptr); /* Call libc free */
  fprintf(stderr, "free(%p)\n", ptr);
}

#endif
