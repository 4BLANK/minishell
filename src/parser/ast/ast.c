/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:01:53 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/14 01:25:06 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

bool	check_token(t_lexeme token_lex, t_token **cur_tok)
{
	if (*cur_tok == NULL)
		return (NULL);
	if ((*cur_tok)->lexem == token_lex)
	{
		*cur_tok = (*cur_tok)->next;
		return (true);
	}
	*cur_tok = (*cur_tok)->next;
	return (false);
}

t_ast_node	*ast_create_node(t_node_type type, t_argument *args, t_file *files)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->u_data.s_childs.right = NULL;
	new_node->u_data.s_childs.left = NULL;
	if (args != NULL)
		new_node->u_data.arg_list = args;
	else if (files != NULL)
		new_node->u_data.files = files;
	return (new_node);
}

void	get_files_and_args(t_file **files, t_argument **args, t_token **tok)
{
	int		lex_tmp;
	void	*tmp;

	while (*tok != NULL && is_schar((*tok)->lexem) != 2)
	{
		if (is_schar((*tok)->lexem) == 1)
		{
			lex_tmp = (*tok)->lexem;
			*tok = (*tok)->next;
			if ((*tok)->lexem == AMBIGUOUS)
				lex_tmp = AMBIGUOUS;
			tmp = (t_file *)new_file(ft_strdup((*tok)->content), lex_tmp);
			if (tmp == NULL)
				return ;
			addfile_back(files, tmp);
		}
		else if (is_schar((*tok)->lexem) == 0)
		{
			tmp = (t_argument *)ft_argsnew(ft_strdup((*tok)->content));
			if (tmp == NULL)
				return ;
			ft_argsadd_back(args, tmp);
		}
		*tok = (*tok)->next;
	}
}

t_ast_node	*form_command(t_token **tokenlst)
{
	t_file		*files;
	t_argument	*args;
	t_ast_node	*command;

	args = NULL;
	files = NULL;
	command = NULL;
	get_files_and_args(&files, &args, tokenlst);
	command = ast_create_node(COMMAND, NULL, NULL);
	if (command == NULL)
		return (NULL);
	command->u_data.s_childs.left = ast_create_node(ARGUMENTS, args, NULL);
	command->u_data.s_childs.right = ast_create_node(REDIRECTION, NULL, files);
	return (command);
}

t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*ast;
	t_token		*cur_token;

	ast = NULL;
	cur_token = NULL;
	if (tokens == NULL)
		return (NULL);
	cur_token = tokens;
	ast = command_line(&cur_token);
	if (cur_token != NULL)
	{
		print_error("ast error!\n", 2);
		return (NULL);
	}
	return (ast);
}
