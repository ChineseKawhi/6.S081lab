#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"

char **parse(char *s)
{
  static char *execargs[12];
  static char buf[1024];
  char *p = buf;
  char *q = buf;
  int i = 0;
  int j = 0;
  while (i < strlen(s))
  {
    if (s[i] == ' ')
    {
      execargs[j++] = p;
      *q++ = 0;
      p = q;
    }
    else if (s[i] == '\n')
    {
      execargs[j++] = p;
      *q++ = 0;
    }
    else
    {
      *q++ = s[i];
    }
    i++;
  }

  return execargs;
}

int main(int argc, char *argv[])
{
  static char *as[8];
  char **xas;
  char buf[1024];
  int n, m;
  m = 0;

  for (int i = 1; i < argc; i++)
  {
    as[i - 1] = argv[i];
  }
  while ((n = read(0, buf + m, sizeof(buf) - m - 1)) > 0)
  {
    xas = parse(buf + m);
    m += n;
    for (int i = 0; xas[i] != 0; i++)
    {
      as[argc - 1 + i] = xas[i];
    }
    if (fork() == 0)
      exec(argv[1], as);
  }
  exit(0);
}
