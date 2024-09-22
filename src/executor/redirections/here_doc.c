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

char *create_tmp()
{
    t_tmps *node;
    t_tmps *tmp;
    char *str;

    str = NULL;
    node = NULL;
    str = create_file_name();
    node = ft_calloc(sizeof(t_tmps), 1);
    if (!node)
        return (NULL);
    node->filename = str;
    node->next = NULL;
    tmp = sh->tmps;
    if (!(sh->tmps))
        sh->tmps = node;
    while (sh->tmps->next)
        sh->tmps = sh->tmps->next;
    sh->tmps->next = node;
    sh->tmps = tmp;
    return (str);
}

void here_doc(char **delimiter)
{
  int fd;
  char *line;
  char *file_name;

  line = NULL;
  file_name = create_tmp();
  fd = open(file_name, O_CREAT | O_RDWR, 0644);
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
