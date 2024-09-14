#include "../../../includes/minishell.h"

int execute_command(t_ast_node *node, int left, int right, int pipefd[2])
{
  char **args;
  int status;
  char *cmd_path;

  args = lst_tostrarray(node->data.childs.left->data.arg_list);
  status = 0;
  if (get_commandpath(&cmd_path, args[0], __environ))
  {
    perror("Command not found");
    return (127);
  }
  if (fork() > 0)
  {
    wait(&status);
    if (WIFEXITED(status))
      status = WEXITSTATUS(status);
    return (status);
  }
  else
  {
    if (right)
      dup2(pipefd[1], STDOUT_FILENO);
    if (left)
      dup2(pipefd[0], STDIN_FILENO);
    if (execv(cmd_path, args) < 0)
      return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
  }
}

int execute_pipeline(t_ast_node *node)
{
  int pipefd[2];
  int status;
  int clonefds[2];

  if (pipe(pipefd) == -1)
    return (EXIT_FAILURE);
  clonefds[0] = pipefd[0];
  clonefds[1] = pipefd[1];
  if (node)
  {
    status = execute_command(node->data.childs.left, 0, 1, (int[2]){0, clonefds[1]});
    node = node->data.childs.right;
  }
  while (node != NULL && node->type == PIPELINE)
  {
    close(clonefds[1]);
    pipe(pipefd);
    clonefds[1] = pipefd[1];
    status = execute_command(node->data.childs.left, 1, 1, clonefds);
    close(clonefds[0]);
    clonefds[0] = pipefd[0];
    node = node->data.childs.right;
  }
  clonefds[0] = pipefd[0];
  close(clonefds[1]);
  status = execute_command(node, 1, 0, (int[2]){clonefds[0], 0});
  close(clonefds[0]);
  return (status);
}

int kickoff(t_ast_node *node)
{
  if (node->type == PIPELINE)
    return execute_pipeline(node);
  if (node->type == COMMAND)
    return execute_command(node, 0, 0, NULL);
  return (EXIT_FAILURE);
}
