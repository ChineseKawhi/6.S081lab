#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int pid;
  int p[2];
  char *buf;
  buf = "x";

  pipe(p);
  pid = fork();

  if (pid == 0)
  {
    // child
    // receive byte and print
    read(p[0], buf, 1);
    printf("%d: received ping\n", pid);
    // send byte
    write(p[1], buf, 1);
  }
  else
  {
    // parent
    // send byte
    write(p[1], buf, 1);
    // receive byte and print
    read(p[0], buf, 1);
    printf("%d: received pong\n", pid);
  }
  wait(0);
  close(p[0]);
  close(p[1]);
  exit(0);
}
