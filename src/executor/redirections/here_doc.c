#include "../../../includes/executor.h"

// to redo later
void here_doc(const char *delimiter)
{
  char *tmp;
  int fd;
  char *dest;
  int flag;
  char *del;

  flag = 0;
  dest = NULL;
  del = ft_calloc(ft_strlen(delimiter) + 1, 1);
  del[1] = ' ';
  while (flag == 0)
  {
    tmp = readline("> ");
    if (!ft_strncmp(tmp, delimiter, ft_strlen(delimiter)))
      flag = 1;
    else
      dest = ft_strjoin(dest, tmp);
    free(tmp);
  }
  close(fd);
}
