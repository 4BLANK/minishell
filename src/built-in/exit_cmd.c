#include "../../includes/minishell.h"

static int is_numeric(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (str[i] > '9' || str[i] < '0')
            return (0);
        i++;
    }
    return (1);
}

int exit_cmd(char **args, t_ast_node **ast)
{
  unsigned char status;

  ft_putstr_fd("exit\n", 1);
  if (!args)
  {
    status = sh->ex_status;
    ast_distroy(ast, 1);
    distroy_envlst(&(sh->envlst));
    free(sh);
    exit(status);
  }
  if (args[1])
  {
    if (is_numeric(args[1]))
      status = ft_atoi(args[1]);
    else
    {
      ft_putstr_fd("chnghl o mnghl: exit:", 2);
      ft_putstr_fd(args[1], 2);
      ft_putstr_fd(": numeric agrument required\n", 2);
      distroy_envlst(&(sh->envlst));
      free(sh);
      exit(2);
    }
  }
  else
  status = sh->ex_status;
  if (args[1] && args[2])
  {
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("chnghl o mnghl: exit:", 2);
    ft_putstr_fd(args[1], 2);
    ft_putstr_fd(": too many arguments\n", 2);
    return (EXIT_FAILURE);
  }
  distroy_envlst(&(sh->envlst));
  free(sh);
  exit(status);
}
