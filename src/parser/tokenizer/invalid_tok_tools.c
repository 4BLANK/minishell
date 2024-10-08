/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_tok_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:45:16 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 18:47:28 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_redirection(t_token *tok)
{
	int		red_count;
	int		file_count;
	char	*tmp;

	tmp = NULL;
	red_count = 0;
	file_count = 0;
	if (tok == NULL)
		return (1);
	while (tok != NULL)
	{
		tmp = tok->content;
		if ((tmp[0] != GREATER && tmp[0] != LESS) && schar_detected(tmp[0]))
			break ;
		if (tmp[0] == GREATER || tmp[0] == LESS)
			red_count++;
		else
			file_count++;
		tok = tok->next;
	}
	if (file_count != red_count)
		return (0);
	return (1);
}

int	is_invalid_cparen(char *tmp, t_token *tok, t_token *prev_tok)
{
	if (tmp[0] == CPAREN && (tok->next && (((tok->next->content)[0] == OPAREN) \
					|| ((tok->next->content)[0] != GREATER \
					&& (tok->next->content)[0] != LESS \
					&& !schar_detected((tok->next->content)[0])))))
		return (EXIT_FAILURE);
	if (tmp[0] == CPAREN && ((tok->next \
					&& (!schar_detected((tok->next->content)[0]) \
					&& ((prev_tok->content)[0] != GREATER \
					|| (prev_tok->content)[0] != LESS)))
			|| !check_redirection(tok->next)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
