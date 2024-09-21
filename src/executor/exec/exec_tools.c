#include "../../../includes/minishell.h"

size_t lstsize(t_argument *lst)
{
    int count;
    t_argument *current;
    
    count = 0;
    current = lst;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return (count);
}

void free_strarray(char **str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

static int has_slash(char *str)
{
  size_t i;

  i = 0;
  while (i < ft_strlen(str))
  {
    if (str[i] == '/' || str[i] == '.')
      return (1);
    i++;
  }
  return (0);
}

int tiny_check()
{
  if (has_slash(sh->args[0]) && access(sh->args[0], X_OK))
    return (127);
  return (0);
}

int get_commandpath(char **cmd_path, char *cmd, char **env)
{
  char *path;
  char **paths;
  char *tmp;
  int i;
  
  (void)env;
  i = -1;
  path = getenv("PATH");
  if (path == NULL)
  { 
    *cmd_path = NULL;
    return (EXIT_FAILURE);
  }
  if (!access(cmd, X_OK))
  {
    *cmd_path = ft_strdup(cmd);
    return (EXIT_SUCCESS);
  }
  paths = ft_split(path, ':');
  if (paths == NULL)
    return EXIT_FAILURE;
  tmp = ft_strjoin("/", cmd);
  while (paths[++i] != NULL)
  {
    *cmd_path = ft_strjoin(paths[i], tmp);
    if (!access(*cmd_path, X_OK))
    {
      free(tmp);
      free_strarray(paths);
      return (EXIT_SUCCESS);
    }
    free(*cmd_path);
  }
  free(tmp);
  free_strarray(paths);
  *cmd_path = ft_strdup(cmd);
  return (EXIT_SUCCESS);
}

char **lst_tostrarray(t_argument *head) 
{
  size_t count;
  char **strarray;
  int i;

  i = 0;
  count = 1;
  if (!(count = lstsize(head)))
    return NULL;
  strarray = (char **)ft_calloc(sizeof(char *), (count + 1));
  if (strarray == NULL)
    return NULL;
  while (head != NULL)
  {
    strarray[i] = ft_strdup(head->content);
    if (strarray[i] == NULL)
      return NULL;
    head = head->next;
    i++;
  }
  strarray[i] = NULL;
  return strarray;
}

static int is_dir(char *pwd)
{
  DIR *dir;

  dir = NULL;
  if ((dir = opendir(pwd)) != NULL)
    return (1);
  return (0);
}

int check_error_type(char *cmd_path)
{
  if (access(cmd_path, F_OK) != -1)
    return (126);
  else
    return (127);
  return (0);
}

int specify_error(int status, char *cmd_path)
{
  if (status == 126 || status == 127)
  {
    ft_putstr_fd("chnghl o mnghl: ", 2);
    ft_putstr_fd(cmd_path, 2);
  }
  if (status == 126)
  {
    if (is_dir(cmd_path))
      ft_putstr_fd(": Is a directory\n", 2);
    else
      ft_putstr_fd(": Permission denied\n", 2);
  }
  else if (status == 127)
  {
    if (has_slash(cmd_path))
      ft_putstr_fd(": No such file or directory\n", 2);
    else
      ft_putstr_fd(": Command not found\n", 2);
  }
  return (0);
}
