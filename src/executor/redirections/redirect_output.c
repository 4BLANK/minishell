#include "../../../includes/minishell.h"
#include <stdio.h>

int redirect_output(const char *filename)
{
  int fd;

  fd = open(filename, O_CREAT | O_RDWR, 0644);
  if (fd < 0)
  {
    perror("chnghl omnghl:");
    return (EXIT_FAILURE);
  }
  dup2(fd, 1);
  close(fd);
  return (EXIT_SUCCESS);
}
