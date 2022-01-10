#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main()
{
  char *argv[] = {"echo", "hello", "world", 0};
  close(1);
  if (open("output.txt", O_CREATE | O_RDWR) < 0)
    printf("open fail\n");
  exec("echo", argv);
  printf("exec fail\n");
  exit(0);
}
