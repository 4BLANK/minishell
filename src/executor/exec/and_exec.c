#include "../../../includes/minishell.h"

int execute_and(t_ast_node *node)
{
  int status;

  status = 0;
  while (status == 0 && node != NULL && node->type == AND_NODE)
  {
    if (node->data.childs.left->type == COMMAND)
      status = execute_command(node->data.childs.left, 0, 0, NULL);
    if (node->data.childs.left->type == GROUP_NODE)
      status = execute_group(node->data.childs.left, 0, 0, NULL);
    if (node->data.childs.left->type == PIPELINE)
      status = execute_pipeline(node->data.childs.left);
    node = node->data.childs.right;
  }
  if (status == 0 && node->type == COMMAND)
    status = execute_command(node, 0, 0, NULL);
  if (status == 0 && node->type == GROUP_NODE)
    status = execute_group(node, 0, 0, NULL);
  if (status == 0 && node->type == PIPELINE)
    status = execute_pipeline(node);
  return (status);
}
