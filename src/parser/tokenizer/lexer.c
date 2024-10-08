/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:02:28 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 14:02:35 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	schar_lexer(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (ft_strcmp(tokens->content, ")"))
			tokens->lexem = CLOSE_P;
		else if (ft_strcmp(tokens->content, "("))
			tokens->lexem = OPEN_P;
		else if (ft_strcmp(tokens->content, ">"))
			tokens->lexem = O_REDIRECTION;
		else if (ft_strcmp(tokens->content, "<"))
			tokens->lexem = I_REDIRECTION;
		else if (ft_strcmp(tokens->content, "<<"))
			tokens->lexem = HEREDOC;
		else if (ft_strcmp(tokens->content, ">>"))
			tokens->lexem = APPEND;
		else if (ft_strcmp(tokens->content, "|"))
			tokens->lexem = PIPE;
		else if (ft_strcmp(tokens->content, "||"))
			tokens->lexem = OR;
		else if (ft_strcmp(tokens->content, "&&"))
			tokens->lexem = AND;
		else if (tokens->lexem != AMBIGUOUS)
			tokens->lexem = STRING;
		tokens = tokens->next;
	}
}

void	set_lexeme(t_token *token, t_lexeme prev_lexeme)
{
	if (token->lexem == STRING)
	{
		if (prev_lexeme == PIPE || prev_lexeme == AND || prev_lexeme == OR
			|| prev_lexeme == OPEN_P || prev_lexeme == CLOSE_P)
			token->lexem = CMD;
		else if (prev_lexeme == I_REDIRECTION || prev_lexeme == O_REDIRECTION
			|| prev_lexeme == APPEND)
			token->lexem = O_FILE;
		else if (prev_lexeme == CMD || prev_lexeme == ARG)
			token->lexem = ARG;
	}
}

void	lexer(t_token *tokens)
{
	t_token	*prev_token;
	t_token	*tmp;
	int		red;

	prev_token = NULL;
	tmp = tokens;
	red = 0;
	schar_lexer(tokens);
	while (tokens != NULL)
	{
		if (is_schar(tokens->lexem))
		{
			red++;
			red_lexer(tmp, red);
		}
		if (prev_token != NULL && tokens->lexem == STRING)
			set_lexeme(tokens, prev_token->lexem);
		else if (prev_token != NULL && tokens->lexem != STRING)
			set_lexeme(tokens, PIPE);
		else if (prev_token == NULL && tokens->lexem == STRING)
			tokens->lexem = CMD;
		prev_token = tokens;
		tokens = tokens->next;
	}
}
