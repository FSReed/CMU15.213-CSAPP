#include <malloc.h>

int main() {
  int *ptr = malloc(32);
  free(ptr);
  return 0;
}
