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
