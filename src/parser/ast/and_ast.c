/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:32:13 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/14 01:24:24 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

static t_ast_node	*command_line_and_1(t_token **cur_token);
static t_ast_node	*command_line_and_2(t_token **cur_token);

t_ast_node	*command_line_and(t_token **cur_token)
{
	t_ast_node	*node;
	t_token		*save_token;

	save_token = *cur_token;
	node = command_line_and_1(cur_token);
	if (node != NULL)
		return (node);
	*cur_token = save_token;
	node = command_line_and_2(cur_token);
	if (node != NULL)
		return (node);
	return (NULL);
}

static t_ast_node	*command_line_and_1(t_token **cur_token)
{
	t_ast_node	*cmd_and;
	t_ast_node	*group;
	t_ast_node	*head_node;
	t_token		*save;

	save = *cur_token;
	group = pipe_line(cur_token);
	if (group == NULL)
		return (NULL);
	if (!check_token(AND, cur_token))
	{
		*cur_token = save;
		ast_distroy(&group, 0);
		return (NULL);
	}
	cmd_and = command_line_and(cur_token);
	if (cmd_and == NULL)
		return (NULL);
	head_node = ast_create_node(AND_NODE, NULL, NULL);
	if (head_node == NULL)
		return (NULL);
	head_node->u_data.s_childs.left = group;
	head_node->u_data.s_childs.right = cmd_and;
	return (head_node);
}

static t_ast_node	*command_line_and_2(t_token **cur_token)
{
	return (pipe_line(cur_token));
}
