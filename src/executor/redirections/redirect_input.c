#include "../../../includes/executor.h"

void redirect_input(const char *filename)
{
  int fd;
  char *str;

  fd = open(filename, O_RDONLY);
  if (fd < 0)
    return ;
  dup2(fd, 0);
  close(fd);
}
