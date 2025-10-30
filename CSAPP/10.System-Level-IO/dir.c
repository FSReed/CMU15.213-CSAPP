#include <dirent.h>
#include <stdio.h>

int main(int argc, char **argv) {
  DIR *dir = opendir(argv[1]);
  struct dirent *subdir;
  while ((subdir = readdir(dir)) != 0) {
    printf("%s\n", subdir->d_name);
  }
  return 0;
}
