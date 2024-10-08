/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:01:51 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 14:01:56 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	process_redirection(t_token **tokens, t_lexeme lex);
static void	update_command_flag(t_token *tokens, int *command_flag);
static bool	is_valid_redirection(t_token *tokens, int *itr, int red_nbr);
static void	handle_token_stream(t_token **tokens, int *command_flag);

void	red_lexer(t_token *tokens, int red_nbr)
{
	int			command_flag;
	int			itr;
	t_lexeme	lex;

	itr = 0;
	command_flag = 0;
	while (tokens != NULL)
	{
		update_command_flag(tokens, &command_flag);
		if (is_valid_redirection(tokens, &itr, red_nbr))
		{
			lex = tokens->lexem;
			tokens = tokens->next;
			if (tokens != NULL)
				process_redirection(&tokens, lex);
			handle_token_stream(&tokens, &command_flag);
			break ;
		}
		tokens = tokens->next;
	}
}

static void	update_command_flag(t_token *tokens, int *command_flag)
{
	if (*command_flag == 0 && tokens->lexem == CMD)
		*command_flag = 1;
	else if (*command_flag == 1 && (tokens->lexem == PIPE
			|| tokens->lexem == AND || tokens->lexem == OR
			|| tokens->lexem == OPEN_P || tokens->lexem == CLOSE_P))
		*command_flag = 0;
}

static bool	is_valid_redirection(t_token *tokens, int *itr, int red_nbr)
{
	if (is_schar(tokens->lexem) == 1)
	{
		(*itr)++;
		if (*itr == red_nbr)
			return (true);
	}
	return (false);
}

static void	process_redirection(t_token **tokens, t_lexeme lex)
{
	if (lex == HEREDOC && (*tokens)->lexem != AMBIGUOUS)
		(*tokens)->lexem = DELIMITER;
	else if ((*tokens)->lexem != AMBIGUOUS)
		(*tokens)->lexem = O_FILE;
	*tokens = (*tokens)->next;
}

static void	handle_token_stream(t_token **tokens, int *command_flag)
{
	while (*tokens != NULL && is_schar((*tokens)->lexem) == 0)
	{
		if (*command_flag == 1)
			(*tokens)->lexem = ARG;
		else
		{
			(*tokens)->lexem = CMD;
			*command_flag = 1;
		}
		*tokens = (*tokens)->next;
	}
}
