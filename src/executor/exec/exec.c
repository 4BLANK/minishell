#include "../../../includes/minishell.h"

int kickoff(t_ast_node *node)
{
  if (node->type == AND_NODE)
    return execute_and(node);
  if (node->type == PIPELINE)
    return execute_pipeline(node);
  if (node->type == COMMAND)
    return execute_command(node, (t_pair []){{0, 0}}, NULL, NULL);
  if (node->type == OR_NODE)
    return execute_or(node);
  if (node->type == GROUP_NODE)
    return execute_group(node, (t_pair []){{0, 0}}, NULL, NULL);
  return (EXIT_FAILURE);
}
