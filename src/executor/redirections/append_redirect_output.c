#include "../../../includes/executor.h"
#include <fcntl.h>

void append_redirect_output(const char *filename)
{
  int fd;

  fd = open(filename, O_CREAT | O_APPEND);
  if (fd < 0)
    return ;
  dup2(fd, 1);
  close(fd);
}
