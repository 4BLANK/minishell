/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:01:34 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 03:02:50 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static unsigned char	routine(t_ast_node **node)
{
	unsigned char	status;

	status = 0;
	if ((*node)->data.childs.left->type == COMMAND)
		status = execute_command((*node)->data.childs.left, (t_pair[]){{0, 0}},
				NULL, NULL);
	if ((*node)->data.childs.left->type == GROUP_NODE)
		status = execute_group((*node)->data.childs.left, (t_pair[]){{0, 0}},
				NULL, NULL);
	if ((*node)->data.childs.left->type == PIPELINE)
		status = execute_pipeline((*node)->data.childs.left);
	if ((*node)->data.childs.left->type == OR_NODE)
		status = execute_or((*node)->data.childs.left);
	(*node) = (*node)->data.childs.right;
	if (status == 0 && sh && sh->args)
	{
		free_strarray(sh->args);
		sh->args = NULL;
	}
	return (status);
}

int	execute_and(t_ast_node *node)
{
	unsigned char	status;

	status = 0;
	while (status == 0 && node != NULL && node->type == AND_NODE)
		status = routine(&node);
	if (status == 0 && node->type == COMMAND)
		status = execute_command(node, (t_pair[]){{0, 0}}, NULL, NULL);
	if (status == 0 && node->type == GROUP_NODE)
		status = execute_group(node, (t_pair[]){{0, 0}}, NULL, NULL);
	if (status == 0 && node->type == PIPELINE)
		status = execute_pipeline(node);
	if (status == 0 && node->type == OR_NODE)
		status = execute_or(node);
	return (status);
}
