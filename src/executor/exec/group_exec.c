#include "../../../includes/minishell.h"

int execute_group(t_ast_node *node, int left, int right, int pipefd[2])
{
  int status;
  pid_t pid;

  status = 0;
  pid = fork();
  if (pid > 0)
  {
    wait(&status);
    if (WIFEXITED(status))
      status = WEXITSTATUS(status);
    else
      printf("\n");
    return (status);
  }
  else
  {
    if (right)
      dup2(pipefd[1], STDOUT_FILENO);
    if (left)
      dup2(pipefd[0], STDIN_FILENO);
    exit(kickoff(node->data.childs.left));
  }
  return (status);
}
