/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:36:58 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/14 01:27:22 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

void	clear_fileslst(t_file **lst, int flag)
{
	t_file	*node;
	t_file	*next;

	if (lst && *lst)
	{
		node = *lst;
		while (node != NULL)
		{
			next = node->next;
			if (flag && node->type == HEREDOC)
				unlink(node->name);
			free(node->name);
			free(node);
			node = next;
		}
		*lst = NULL;
	}
}

void	destroy_ast_core(t_ast_node *node, int flag)
{
	if (!node)
		return ;
	if (node->type != REDIRECTION && node->type != ARGUMENTS)
	{
		if (node->u_data.s_childs.left)
			destroy_ast_core(node->u_data.s_childs.left, flag);
		if (node->u_data.s_childs.right)
			destroy_ast_core(node->u_data.s_childs.right, flag);
	}
	else
	{
		if (node->type == REDIRECTION)
			clear_fileslst(&node->u_data.files, flag);
		else if (node->type == ARGUMENTS)
			clear_argslst(&node->u_data.arg_list);
	}
	free(node);
}

void	ast_distroy(t_ast_node **node, int flag)
{
	if (*node)
	{
		destroy_ast_core(*node, flag);
		*node = NULL;
	}
}

void	addfile_back(t_file **lst, t_file *new)
{
	t_file	*node;

	if (new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			node = *lst;
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = new;
		}
	}
}

t_file	*new_file(void *file_name, t_lexeme filetype)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->name = file_name;
	file->type = filetype;
	file->next = NULL;
	return (file);
}
