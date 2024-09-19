#include "../../../includes/minishell.h"

int execute_command(t_ast_node *node, int left, int right, int pipefd[2])
{
  char **args;
  int status;
  char *cmd_path;
  pid_t pid;

  args = lst_tostrarray(node->data.childs.left->data.arg_list);
  status = 0;
  pid = fork();
  if (pid > 0)
  {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
      status = WEXITSTATUS(status);
    else
      printf("\n");
    specify_error(status, cmd_path);
    return (status);
  }
  else
  {
    handle_signals(CHILD);
    if (get_commandpath(&cmd_path, args[0], __environ))
      return (EXIT_FAILURE);
    if (redirect(node, &left, &right))
      exit(EXIT_FAILURE);
    if (right)
      dup2(pipefd[1], STDOUT_FILENO);
    if (left)
      dup2(pipefd[0], STDIN_FILENO);
    if (execv(cmd_path, args) < 0)
      exit(check_error_type(cmd_path));
    exit(EXIT_SUCCESS);
  }
}

int execute_pipeline(t_ast_node *node)
{
  int status;
  int clonefds[2];

  if (pipe(sh->pipefd) == -1)
    return (EXIT_FAILURE);
  clonefds[0] = sh->pipefd[0];
  clonefds[1] = sh->pipefd[1];
  if (node->data.childs.left->type == COMMAND)
    status = execute_command(node->data.childs.left, 0, 1, clonefds);
  if (node->data.childs.left->type == GROUP_NODE)
    status = execute_group(node->data.childs.left, 0, 1, clonefds);
  node = node->data.childs.right;
  while (node != NULL && node->type == PIPELINE)
  {
    close(clonefds[1]);
    pipe(sh->pipefd);
    clonefds[1] = sh->pipefd[1];
    if (node->data.childs.left->type == COMMAND)
      status = execute_command(node->data.childs.left, 1, 1, clonefds);
    if (node->data.childs.left->type == GROUP_NODE)
      status = execute_group(node->data.childs.left, 1, 1, clonefds);
    close(clonefds[0]);
    clonefds[0] = sh->pipefd[0];
    node = node->data.childs.right;
  }
  clonefds[0] = sh->pipefd[0];
  close(clonefds[1]);
  if (node->type == COMMAND)
    status = execute_command(node, 1, 0, clonefds);
  if (node->type == GROUP_NODE)
    status = execute_group(node, 1, 0, clonefds);
  close(clonefds[0]);
  return (status);
}

int kickoff(t_ast_node *node)
{
  if (node->type == AND_NODE)
    return execute_and(node);
  if (node->type == PIPELINE)
    return execute_pipeline(node);
  if (node->type == COMMAND)
    return execute_command(node, 0, 0, NULL);
  if (node->type == OR_NODE)
    return execute_or(node);
  if (node->type == GROUP_NODE)
    return execute_group(node, 0, 0, NULL);
  return (EXIT_FAILURE);
}
