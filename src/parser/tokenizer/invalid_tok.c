/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:00:27 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 18:47:07 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_invalid_pipe_and(char *tmp, t_token *tok, t_token *prev_tok);
int	is_invalid_greater_less(char *tmp, t_token *tok);
int	is_invalid_tok_seq(char *tmp, t_token *tok);
int	is_invalid_oparen(char *tmp, t_token *tok, t_token *prev_tok);
int	is_invalid_cparen(char *tmp, t_token *tok, t_token *prev_tok);

int	is_invalid_special_char(char *tmp, t_token *tok, t_token *prev_tok)
{
	if (ft_strlen(tmp) > 2)
		return (EXIT_FAILURE);
	if (is_invalid_pipe_and(tmp, tok, prev_tok))
		return (EXIT_FAILURE);
	if (is_invalid_greater_less(tmp, tok))
		return (EXIT_FAILURE);
	if (is_invalid_tok_seq(tmp, tok))
		return (EXIT_FAILURE);
	if (tmp[0] == OPAREN && is_invalid_oparen(tmp, tok, prev_tok))
		return (EXIT_FAILURE);
	if (tmp[0] == CPAREN && is_invalid_cparen(tmp, tok, prev_tok))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_invalid_pipe_and(char *tmp, t_token *tok, t_token *prev_tok)
{
	if ((tmp[0] == CPIPE || (ft_strncmp(tmp, "&&", 2) == 0))
		&& (tok->next == NULL || prev_tok == NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_invalid_greater_less(char *tmp, t_token *tok)
{
	if ((tmp[0] == GREATER || tmp[0] == LESS) && (!(tok->next)
			|| schar_detected((tok->next)->content[0])))
		return (EXIT_FAILURE);
	else if (tmp[0] == GREATER && (tok->content)[0] == LESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_invalid_tok_seq(char *tmp, t_token *tok)
{
	if (tok->next && (tmp[0] != OPAREN && tmp[0] != CPAREN) && ft_strcmp(tmp,
			tok->next->content))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_invalid_oparen(char *tmp, t_token *tok, t_token *prev_tok)
{
	if (tmp[0] == OPAREN && (!(tok->next) || (tok->next)->content[0] == CPAREN))
		return (EXIT_FAILURE);
	if (tmp[0] == OPAREN && (prev_tok != NULL \
				&& (!schar_detected((prev_tok->content)[0]) \
				&& ((prev_tok->content)[0] != GREATER \
				|| (prev_tok->content)[0] != LESS))))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
