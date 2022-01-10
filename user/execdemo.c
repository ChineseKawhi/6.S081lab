#include "kernel/types.h"
#include "user/user.h"

int main()
{
  char *argv[] = {"echo", "hello", "world", 0};
  exec("echo", argv);
  printf("exec fail\n");
  exit(0);
}
