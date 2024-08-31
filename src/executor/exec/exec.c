#include "../../../includes/minishell.h"

int execute_simple_command(char *const *argv, int fd[2])
{
  dup2(fd[0], STDIN_FILENO);
  dup2(fd[1], STDOUT_FILENO);
  close(fd[0]);
  close(fd[1]);
  return (execv(argv[0], argv));
}

int execute_command(t_argument *args_list)
{

}

int execute_pipeline(t_ast_node *node)
{
  int pipefd[2];

  pipe(pipefd);
  execute_pipeline();
}
