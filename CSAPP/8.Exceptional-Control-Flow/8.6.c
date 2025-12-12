#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
  printf("\nCommand-link Arguments:\n");
  for (int i = 0; i < argc; ++i) {
    printf("arg[%d]: %s\n", i, argv[i]);
  }

  printf("\nEnvironment Variables:\n");
  int env_num = 0;
  while (*envp != NULL) {
    printf("envp[%d]: %s\n", env_num, *envp);
    ++env_num;
    ++envp;
  }
  return 0;
}
