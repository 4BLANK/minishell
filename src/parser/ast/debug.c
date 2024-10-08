/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:41:02 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 20:04:36 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*lexs_type[] = {"STRING", "ARG", "PIPE", "FILE", "CMD", "I_RED",
		"O_RED", "HERDOC", "DELIMITER", "AMBIGUOUS", "APPEND", "AND", "OR",
		"OPEN_P", "CLOSE_P"};

char	*ast_node_types[] = {"GROUP", "AND", "OR", "PIPELINE", "COMMAND",
		"REDIRECTION", "ARGUMENTS"};

void	print_args(t_argument *args)
{
	while (args != NULL)
	{
		printf(" %s ->", args->content);
		args = args->next;
	}
	printf(" null");
}

void	print_files(t_file *files)
{
	while (files != NULL)
	{
		printf(" %s(%s) ->", files->name, lexs_type[files->type]);
		files = files->next;
	}
	printf(" null");
}

void	print_space(int space)
{
	int	i;

	i = -1;
	while (++i < space)
		printf("  ");
}

void	print_ast_tree(t_ast_node *ast_tree, int space)
{
	if (ast_tree == NULL)
		return ;
	print_space(space);
	printf(" > %s ", ast_node_types[ast_tree->type]);
	if (ast_tree->type == ARGUMENTS)
	{
		printf("|");
		print_args(ast_tree->data.arg_list);
	}
	else if (ast_tree->type == REDIRECTION)
	{
		printf("|");
		print_files(ast_tree->data.files);
	}
	printf("\n");
	if (ast_tree->type == COMMAND || ast_tree->type == PIPELINE
		|| ast_tree->type == AND_NODE || ast_tree->type == OR_NODE
		|| ast_tree->type == GROUP_NODE)
	{
		if (ast_tree->data.childs.left != NULL)
			print_ast_tree(ast_tree->data.childs.left, space + 1);
		else
		{
			print_space(space + 1);
			printf("\n");
		}
		if (ast_tree->data.childs.right != NULL)
			print_ast_tree(ast_tree->data.childs.right, space + 1);
		else
		{
			print_space(space + 1);
			printf("\n");
		}
	}
}
