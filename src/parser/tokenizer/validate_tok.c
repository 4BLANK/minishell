/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:05:06 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/15 19:48:31 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	process_heredoc(t_token *tok, t_token **toklst);
static int	is_quoted(char *str);
static int	chack_parn(t_token *tokenlst);

int	validate_token(t_token **tokenlst)
{
	t_token	*tok;
	t_token	*prev_tok;
	int		status;

	tok = *tokenlst;
	prev_tok = NULL;
	if (chack_parn(tok))
		return (EXIT_FAILURE);
	while (tok != NULL)
	{
		if (schar_detected((tok->content)[0]))
		{
			if (is_invalid_special_char(tok->content, tok, prev_tok))
				return (s_error(tok->next));
		}
		if (ft_strcmp(tok->content, "<<"))
		{
			status = process_heredoc(tok, tokenlst);
			if (status != 0)
				return (status);
		}
		prev_tok = tok;
		tok = tok->next;
	}
	return (EXIT_SUCCESS);
}

int	s_error(t_token *tok)
{
	char	*tmp;

	if (tok == NULL)
		tmp = "newline";
	else
		tmp = tok->content;
	ft_putstr_fd("mongol: syntax error near unexpected token", 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd("'\n", 2);
	return (PARSE_ERROR);
}

static int	process_heredoc(t_token *tok, t_token **toklst)
{
	int	flag;

	flag = 0;
	if (!is_quoted((tok->next)->content))
		flag = 1;
	(tok->next)->content = remove_quote((tok->next)->content);
	return (here_doc(&(tok->next)->content, flag, toklst));
}

static int	is_quoted(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == DQUOTE)
			return (1);
		i++;
	}
	return (0);
}

static int	chack_parn(t_token *tokenlst)
{
	t_token	*tok;
	char	*tmp;
	int		p_count;

	tok = tokenlst;
	tmp = NULL;
	p_count = 0;
	while (tok != NULL)
	{
		tmp = tok->content;
		if (tmp[0] == OPAREN)
			p_count++;
		else if (tmp[0] == CPAREN)
			p_count--;
		tok = tok->next;
	}
	if (p_count > 0)
		return (print_error("unclosed parenthesis\n", 1));
	else if (p_count < 0)
		return (print_error("unclosed parenthesis\n", 1));
	return (EXIT_SUCCESS);
}
