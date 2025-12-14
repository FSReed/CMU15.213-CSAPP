#include <setjmp.h>
#include <stdio.h>

jmp_buf env;

void foo();
void bar();

void foo() {
  longjmp(env, 1);
  bar();
}

void bar() {
  longjmp(env, 2);
}

int main(int argc, char *argv[])
{
  switch (setjmp(env)) {
  case 0:
    foo();
    break;
  case 1:
    printf("error 1\n");
    break;
  case 2:
    printf("error 2\n");
    break;
  default:
    printf("Never reached\n");
  }
  return 0;
}
