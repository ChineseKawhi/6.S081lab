#include "kernel/types.h"
#include "user/user.h"

void generate(int lp[2])
{
  int rp[2];
  int c;
  c = 0;

  if (read(lp[0], &c, 1) == 0)
  {
    exit(0);
  }
  printf("prime %d\n", c);

  pipe(rp);
  if (fork() == 0)
  {
    close(rp[1]);
    generate(rp);
  }
  close(rp[0]);
  int r;
  r = 0;
  while (read(lp[0], &r, 1) != 0)
  {
    if (r % c != 0)
    {
      write(rp[1], &r, 1);
    }
  }
  close(lp[0]);
  close(rp[1]);
  wait(0);
  exit(0);
}

int main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  close(0);
  if (fork() == 0)
  {
    close(p[1]); // 1
    generate(p);
  }
  close(p[0]); // 3
  for (int i = 2; i <= 35; i++)
  {
    write(p[1], &i, 1);
  }
  close(p[1]); // 4
  wait(0);
  exit(0);
}
