#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  execve("/bin/ls", argv, __environ);
}
