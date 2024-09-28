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

static int child_routine(char **delimiter, int fd, int flag)
{
    char *line;

    line = NULL;
    handle_signals(HDOC);
    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
        {
            ft_putstr_fd("chnghl o mnghl: warning: here-document delimited by EOF, wanted: ", 2);
            ft_putstr_fd(*delimiter, 2);
            ft_putstr_fd("\n", 2);
            return (EXIT_FAILURE);
        }
        if (!ft_strcmp(*delimiter, line))
        {
            if (flag == 1)
            {
                printf("expand\n");
                line = expand_heredoc(line);
            }
            ft_putstr_fd(line, fd);
            ft_putstr_fd("\n", fd); 
        }
        else
            return (EXIT_SUCCESS);
    }
}

int here_doc(char **delimiter, int flag)
{
  int fd;
  char *file_name;
  pid_t pid; 
  int status;

  file_name = create_tmp();
  fd = open(file_name, O_CREAT | O_RDWR, 0644);
  status = 0;
  if (fd < 0)
      return (EXIT_FAILURE);
  pid = fork();
  if (pid > 0)
  {
      waitpid(pid, &status, 0);
      if (WIFEXITED(status))
          status = WEXITSTATUS(status);
      else
      {
          //*status = WTERMSIG(*status);
          printf("\n");
          status += 128;
      }
      if (!status)
      {
          free(*delimiter);
          *delimiter = file_name;
      }
  }
  else if (pid == 0)
      exit(child_routine(delimiter, fd, flag));
  return (status);
}
