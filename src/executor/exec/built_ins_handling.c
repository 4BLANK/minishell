#include "../../../includes/minishell.h"

int is_built_in(char *str)
{
  return (!(ft_strncmp(str, "pwd", 4)) || !(ft_strncmp(str, "echo", 5))\
   || !(ft_strncmp(str, "exit", 5)) || !(ft_strncmp(str, "env", 4)) \
   || !(ft_strncmp(str, "export", 7)) || !(ft_strncmp(str, "cd", 3))\
   || !(ft_strncmp(str, "unset", 6)));
}

int execute(t_ast_node *node, t_pair *pl, int pipefd[2])
{
  if (!is_built_in(sh->args[0]))
    return (0);
  int save[2];
  save[0] = dup(STDIN_FILENO);
  save[1] = dup(STDOUT_FILENO);
  if (redirect(node, &(pl->left), &(pl->right)))
    return (EXIT_FAILURE);
  if (pl->right)
    dup2(pipefd[1], STDOUT_FILENO);
  if (pl->left)
    dup2(pipefd[0], STDIN_FILENO);
  if (!ft_strncmp(sh->args[0], "pwd", 3))
    sh->ex_status = pwd_cmd(sh->args);
  if (!ft_strncmp(sh->args[0], "echo", 4))
    sh->ex_status = echo(sh->args);
  if (!ft_strncmp(sh->args[0], "env", 3))
    sh->ex_status = env_cmd();
  if (!ft_strncmp(sh->args[0], "exit", 4))
    sh->ex_status = exit_cmd(sh->args, &(sh->ast));
  if (!ft_strncmp(sh->args[0], "export", 6))
    sh->ex_status = export_cmd(sh->args);
  if (!ft_strncmp(sh->args[0], "cd", 2))
    sh->ex_status = cd_cmd(sh->args);
  if (!ft_strncmp(sh->args[0], "unset", 5))
    sh->ex_status = unset_cmd(sh->args);
  dup2(save[0], STDIN_FILENO);
  dup2(save[1], STDOUT_FILENO);
  return (1);
}

int under_pipes(t_ast_node *node, t_pair *l, int pipefd[2])
{
  int pid;

  pid = fork();
  if (pid > 0)
  {
    waitpid(pid, (int *)&(sh->ex_status), 0);
    if (WIFEXITED(sh->ex_status))
      sh->ex_status = WEXITSTATUS(sh->ex_status);
    else
      ft_printf("\n");
    return (1);
  }
  else if (pid == -1)
    exit(EXIT_FAILURE);
  else
  {
    execute(node, l, pipefd);
    exit(free_mem(1));
  }
}

int built_ins(t_ast_node *node, t_pair *pl, int pipefd[2])
{
  if (is_built_in(sh->args[0]) && (pl->right || pl->left))
    return (under_pipes(node, pl, pipefd));
  else if (is_built_in(sh->args[0]) && !(pl->right || pl->left))
    return (execute(node, pl, pipefd));
  return (0);
}
