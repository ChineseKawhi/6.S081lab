#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"

char *
fmtname(char *path)
{
  static char buf[DIRSIZ + 1];
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  // Return blank-padded name.
  if (strlen(p) >= DIRSIZ)
    return p;
  strcpy(buf, p);
  return buf;
}

void find(char *path, char *target)
{
  // printf("find %s in %s.\n", target, path);
  int fd;
  struct stat st;
  char buf[512], *p;
  struct dirent de;

  if ((fd = open(path, 0)) < 0)
  {
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0)
  {
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  strcpy(buf, path);
  p = buf + strlen(buf);
  switch (st.type)
  {
  case T_FILE:
    if (strcmp(fmtname(path), target) == 0)
    {
      *p++ = '\n';
      write(1, buf, strlen(path) + 1);
    }
    break;
  case T_DIR:
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0)
      {
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0)
      {
        find(buf, target);
      }
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}
