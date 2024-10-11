#include "../../../includes/minishell.h"

static unsigned char	routine(t_ast_node **node)
{
	unsigned char	status;

	status = 1;
	if ((*node)->data.childs.left->type == COMMAND)
		status = execute_command((*node)->data.childs.left, (t_pair[]){{0, 0}},
				NULL, NULL);
	if ((*node)->data.childs.left->type == AND_NODE)
		status = execute_and((*node)->data.childs.left);
	if ((*node)->data.childs.left->type == GROUP_NODE)
		status = execute_group((*node)->data.childs.left, (t_pair[]){{0, 0}},
				NULL, NULL);
	if ((*node)->data.childs.left->type == PIPELINE)
		status = execute_pipeline((*node)->data.childs.left);
	(*node) = (*node)->data.childs.right;
	if (status != 0 && sh && sh->args)
		free_strarray(sh->args);
	return (status);
}

int	execute_or(t_ast_node *node)
{
	unsigned char	status;

	status = 1;
	while (status != 0 && status != 130 && node != NULL && node->type == OR_NODE)
		status = routine(&node);
	if (status != 0 && status != 130 && node->type == AND_NODE)
		status = execute_and(node);
	if (status != 0 && status != 130 && node->type == COMMAND)
		status = execute_command(node, (t_pair[]){{0, 0}}, NULL, NULL);
	if (status != 0 && status != 130 && node->type == GROUP_NODE)
		status = execute_group(node, (t_pair[]){{0, 0}}, NULL, NULL);
	if (status != 0 && status != 130 && node->type == PIPELINE)
		status = execute_pipeline(node);
	return (status);
}
