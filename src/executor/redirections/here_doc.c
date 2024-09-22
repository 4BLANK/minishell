#include "../../../includes/minishell.h"

char *create_file_name()
{
  static int num = 0;
  char *str;
  char *res;
  char *num_value;

  res = NULL;
  num_value = ft_itoa(num);
  str = "/tmp/heredoc_tmp";
  res = ft_strjoin(str, num_value);
  free(num_value);
  num++;
  return (res);
}
// to redo later
void here_doc(char **delimiter)
{
  int fd;
  char *line;
  char *file_name;

  line = NULL;
  file_name = create_file_name();
  fd = open(file_name, O_CREAT | O_RDWR);
  if (fd < 0)
    return ;
  while (1)
  {
    line = readline("heredoc> ");
    if (!line)
      return ;
    if (!ft_strcmp(*delimiter, line))
    {
      ft_putstr_fd(line, fd);
      ft_putstr_fd("\n", fd);
    }
    else
    {
      free(*delimiter);
      *delimiter = file_name;
      return ;
    }
  }
}
