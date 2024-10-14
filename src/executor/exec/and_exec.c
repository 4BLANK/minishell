/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:01:34 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/14 02:32:15 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static unsigned char	routine(t_ast_node **node)
{
	unsigned char	status;

	status = 0;
	if ((*node)->u_data.s_childs.left->type == COMMAND)
		status = execute_command((*node)->u_data.s_childs.left, \
		(t_pair[]){{0, 0}},
				NULL, NULL);
	if ((*node)->u_data.s_childs.left->type == GROUP_NODE)
		status = execute_group((*node)->u_data.s_childs.left, \
		(t_pair[]){{0, 0}},
				NULL, NULL);
	if ((*node)->u_data.s_childs.left->type == PIPELINE)
		status = execute_pipeline((*node)->u_data.s_childs.left);
	if ((*node)->u_data.s_childs.left->type == OR_NODE)
		status = execute_or((*node)->u_data.s_childs.left);
	(*node) = (*node)->u_data.s_childs.right;
	if (status == 0 && g_sh && g_sh->args)
	{
		free_strarray(g_sh->args);
		g_sh->args = NULL;
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
