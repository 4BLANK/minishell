#include "../../../includes/minishell.h"

int juice(t_ast_node *node, int left, int right)
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
    return execute_group(node);
  return (EXIT_FAILURE);
}
