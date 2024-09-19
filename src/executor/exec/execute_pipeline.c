#include "../../../includes/minishell.h"

int start_of_piping(t_ast_node *node, int (*clonefds)[2])
{
  int status;
  status = 0;

  if (pipe(sh->pipefd) == -1)
    return (EXIT_FAILURE);
  (*clonefds)[0] = sh->pipefd[0];
  (*clonefds)[1] = sh->pipefd[1];
  if (node->data.childs.left->type == COMMAND)
    status = execute_command(node->data.childs.left, 0, 1, *clonefds);
  if (node->data.childs.left->type == GROUP_NODE)
    status = execute_group(node->data.childs.left, 0, 1, *clonefds);
  return (status);
}

int middle_of_piping(t_ast_node *node, int (*clonefds)[2])
{
  int status;
  status = 0;

  close((*clonefds)[1]);
  pipe(sh->pipefd);
  (*clonefds)[1] = sh->pipefd[1];
  if (node->data.childs.left->type == COMMAND)
    status = execute_command(node->data.childs.left, 1, 1, *clonefds);
  if (node->data.childs.left->type == GROUP_NODE)
    status = execute_group(node->data.childs.left, 1, 1, *clonefds);
  close((*clonefds)[0]);
  (*clonefds)[0] = sh->pipefd[0];
  return (status);
}

int end_of_piping(t_ast_node *node, int (*clonefds)[2])
{
  int status;
  status = 0;

  close((*clonefds)[1]);
  if (node->type == COMMAND)
    status = execute_command(node, 1, 0, *clonefds);
  if (node->type == GROUP_NODE)
    status = execute_group(node, 1, 0, *clonefds);
  close((*clonefds)[0]);
  return (status);
}

int execute_pipeline(t_ast_node *node)
{
  int status;
  int clonefds[2];
  status = 0;

  status = start_of_piping(node, &clonefds);
  node = node->data.childs.right;
  while (node != NULL && node->type == PIPELINE)
  {
    status = middle_of_piping(node, &clonefds);
    node = node->data.childs.right;
  }
  clonefds[0] = sh->pipefd[0];
  status = end_of_piping(node, &clonefds);
  return (status);
}
