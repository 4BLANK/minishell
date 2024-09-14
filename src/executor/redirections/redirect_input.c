#include "../../../includes/minishell.h"

int redirect_input(const char *filename)
{
  int fd;

  fd = open(filename, O_RDONLY, 0644);
  if (fd < 0)
  {
    perror("chnghl omnghl:");
    return (EXIT_FAILURE);
  }
  dup2(fd, 0);
  close(fd);
  return (EXIT_SUCCESS);
}
