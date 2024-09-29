#include "../../../includes/minishell.h"

int is_built_in(char *str)
{
  return (!(ft_strncmp(str, "pwd", 4)) || !(ft_strncmp(str, "echo", 5))\
   || !(ft_strncmp(str, "exit", 5)) || !(ft_strncmp(str, "env", 4)) \
   || !(ft_strncmp(str, "export", 7)) || !(ft_strncmp(str, "cd", 3))\
   || !(ft_strncmp(str, "unset", 6)));
}

int execute(char **args, t_pair *pipe_location, int pipefd[2], int *status)
{
    if (!is_built_in(args[0]))
        return (0);
    if (pipe_location->right)
        dup2(pipefd[1], STDOUT_FILENO);
    if (pipe_location->left)
        dup2(pipefd[0], STDIN_FILENO);
    if (!ft_strncmp(args[0], "pwd", 3))
        *status = pwd_cmd(args);
    if (!ft_strncmp(args[0], "echo", 4))
        *status = echo(args);
    if (!ft_strncmp(args[0], "env", 3))
        *status = env_cmd();
    if (!ft_strncmp(args[0], "exit", 4))
        *status = exit_cmd(args);
    if (!ft_strncmp(args[0], "export", 6))
        *status = export_cmd(args);
    if (!ft_strncmp(args[0], "cd", 2))
        *status = cd_cmd(args);
    if (!ft_strncmp(args[0], "unset", 5))
        *status = unset_cmd(args);
    return (1);
}

int under_pipes(int *status, char **args, t_pair *l, int pipefd[2])
{
  int pid;

  pid = fork();
  if (pid > 0)
  {
    waitpid(pid, status, 0);
    if (WIFEXITED(*status))
      *status = WEXITSTATUS(*status);
    else
      ft_printf("\n");
    return (1);
  }
  else if (pid == -1)
    exit(EXIT_FAILURE);
  else
  {
    execute(args, l, pipefd, status);
    exit(*status);
  }
}

int built_ins(char **args, int *status, t_pair *l, int pipefd[2])
{
    if (is_built_in(args[0]) && (l->right || l->left))
        return (under_pipes(status, args, l, pipefd));
    else if (is_built_in(args[0]) && !(l->right || l->left))
        return (execute(args, l, pipefd, status));
    return (0);
}
