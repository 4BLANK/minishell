/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:34:17 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/06 13:36:03 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

static t_ast_node	*command_line_or_1(t_token **cur_token);
static t_ast_node	*command_line_or_2(t_token **cur_token);

t_ast_node	*command_line_or(t_token **cur_token)
{
	t_ast_node	*node;
	t_token		*save_token;

	save_token = *cur_token;
	node = command_line_or_1(cur_token);
	if (node != NULL)
		return (node);
	*cur_token = save_token;
	node = command_line_or_2(cur_token);
	if (node != NULL)
		return (node);
	return (NULL);
}

static t_ast_node	*command_line_or_1(t_token **cur_token)
{
	t_ast_node	*cmd_and_1;
	t_ast_node	*cmd_and_2;
	t_ast_node	*head_node;
	t_token		*save;

	save = *cur_token;
	cmd_and_1 = command_line_and(cur_token);
	if (cmd_and_1 == NULL)
		return (NULL);
	if (!check_token(OR, cur_token))
	{
		*cur_token = save;
		return (ast_distroy(&cmd_and_1, 0), NULL);
	}
	cmd_and_2 = command_line_or(cur_token);
	if (cmd_and_2 == NULL)
	{
		return (ast_distroy(&cmd_and_1, 0), NULL);
	}
	head_node = ast_create_node(OR_NODE, NULL, NULL);
	if (head_node == NULL)
		return (NULL);
	head_node->data.childs.left = cmd_and_1;
	head_node->data.childs.right = cmd_and_2;
	return (head_node);
}

static t_ast_node	*command_line_or_2(t_token **cur_token)
{
	return (command_line_and(cur_token));
}
