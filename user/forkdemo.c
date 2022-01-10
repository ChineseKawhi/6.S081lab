#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int pid = fork();
  if (pid > 0)
  {
    printf("parent\n");
  }
  else if (pid == 0)
  {
    printf("child\n");
  }
  else
  {
    printf("fork error\n");
  }
  exit(0);
}
