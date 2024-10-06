/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:46:31 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/06 13:55:35 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

static t_ast_node	*grouped_command_1(t_token **cur_token);
static t_ast_node	*grouped_command_0(t_token **cur_token);
static t_file		*get_files(t_token **tokenlst);

t_ast_node	*grouped_command(t_token **cur_token)
{
	t_ast_node	*node;
	t_token		*save_token;

	save_token = *cur_token;
	node = grouped_command_0(cur_token);
	if (node != NULL)
		return (node);
	*cur_token = save_token;
	node = grouped_command_1(cur_token);
	if (node != NULL)
		return (node);
	return (NULL);
}

static t_file	*get_files(t_token **tokenlst)
{
	t_file	*files;
	t_file	*tmp;
	int		lex_tmp;

	files = NULL;
	tmp = NULL;
	if (*tokenlst == NULL || is_schar((*tokenlst)->lexem) != 1)
		return (NULL);
	while (*tokenlst != NULL && is_schar((*tokenlst)->lexem) != 2)
	{
		if (is_schar((*tokenlst)->lexem) == 1)
		{
			lex_tmp = (*tokenlst)->lexem;
			*tokenlst = (*tokenlst)->next;
			tmp = new_file(ft_strdup((*tokenlst)->content), lex_tmp);
			if (tmp == NULL)
				return (NULL);
			addfile_back(&files, tmp);
		}
		*tokenlst = (*tokenlst)->next;
	}
	return (files);
}

static t_ast_node	*grouped_command_0(t_token **cur_token)
{
	t_ast_node	*cmd;
	t_ast_node	*group;
	t_file		*files;

	cmd = NULL;
	files = NULL;
	if (!check_token(OPEN_P, cur_token))
		return (NULL);
	cmd = command_line(cur_token);
	if (cmd == NULL)
		return (NULL);
	if (!check_token(CLOSE_P, cur_token) || (!*cur_token
			|| is_schar((*cur_token)->lexem) != 1))
		return (ast_distroy(&cmd, 0), NULL);
	else
	{
		files = get_files(cur_token);
		group = ast_create_node(GROUP_NODE, NULL, NULL);
		if (files == NULL || group == NULL)
			return (ast_distroy(&cmd, 0), NULL);
		group->data.childs.left = cmd;
		group->data.childs.right = ast_create_node(REDIRECTION, NULL, files);
	}
	return (group);
}

static t_ast_node	*grouped_command_1(t_token **cur_token)
{
	t_ast_node	*cmd;
	t_ast_node	*group;

	cmd = NULL;
	if (!check_token(OPEN_P, cur_token))
		return (NULL);
	cmd = command_line(cur_token);
	if (cmd == NULL)
		return (NULL);
	if (!check_token(CLOSE_P, cur_token))
	{
		ast_distroy(&cmd, 0);
		return (NULL);
	}
	group = ast_create_node(GROUP_NODE, NULL, NULL);
	if (group == NULL)
		return (NULL);
	group->data.childs.left = cmd;
	group->data.childs.right = NULL;
	return (group);
}
