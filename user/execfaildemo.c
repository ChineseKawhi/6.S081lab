#include "kernel/types.h"
#include "user/user.h"

int main()
{
  char *argv[] = {"abc", "hello", "world", 0};
  exec("abc", argv);
  printf("exec fail\n");
  exit(0);
}
