#include "../../includes/minishell.h"

size_t str_arraysize(char **str)
{
    size_t len;

    len = 0;
    if (str == NULL)
        return len;
    while (str[len])
        len++;
    return (len);
}

t_shell *setshell(char **env)
{
  t_shell *sh;

  sh = (t_shell *)ft_calloc(sizeof(t_shell), 1);
  if (sh == NULL)
    return NULL;
  sh->ast = NULL;
  sh->args = NULL;
  sh->envlst = init_envlist(env);
  sh->ex_status = 0;
  return (sh);
}
