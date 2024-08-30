#include "../../../includes/executor.h"
#include <fcntl.h>

void redirect_output(const char *filename)
{
  int fd;

  fd = open(filename, O_CREAT | O_WRONLY);
  if (fd < 0)
    return ;
  dup2(fd, 1);
  close(fd);
}
