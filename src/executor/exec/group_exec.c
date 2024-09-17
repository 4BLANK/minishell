#include "../../../includes/minishell.h"

int execute_group(t_ast_node *node, int left, int right, int clonefds[2])
{
  int status;
  pid_t pid;

  status = 0;
  pid = fork();
  if (pid > 0)
  {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
      status = WEXITSTATUS(status);
    else
      printf("\n");
    return (status);
  }
  else
  {
    if (redirect(node, &left, &right))
      exit(EXIT_FAILURE);
    if (right)
      dup2(clonefds[1], STDOUT_FILENO);
    if (left)
      dup2(clonefds[0], STDIN_FILENO);
    exit(kickoff(node->data.childs.left));
  }
  return (status);
}
