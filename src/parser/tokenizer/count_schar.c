/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_schar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:10:38 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 18:47:00 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	handle_ampersand(char *line, ssize_t i)
{
	size_t	count;

	count = 0;
	if (!i || line[i - 1] != AMPERSAND)
	{
		if (line[i + 1] && line[i + 1] == AMPERSAND)
			count++;
	}
	return (count);
}

size_t	count_operator(char *line, ssize_t i)
{
	size_t	count;

	count = 0;
	if (line[i] == OPAREN || line[i] == CPAREN)
		count++;
	else if (line[i] == GREATER && (!i || line[i - 1] != GREATER))
		count++;
	else if (line[i] == LESS && (!i || line[i - 1] != LESS))
		count++;
	else if (line[i] == CPIPE && (!i || line[i - 1] != CPIPE))
		count++;
	return (count);
}

size_t	count_schar(char *line)
{
	ssize_t	i;
	int		flag;
	size_t	count;

	i = -1;
	flag = 0;
	count = 0;
	while (line[++i])
	{
		flag = toggle_quotes(line[i], flag);
		if (flag == 0 && schar_detected(line[i]))
		{
			if (line[i] == AMPERSAND)
				count += handle_ampersand(line, i);
			else
				count += count_operator(line, i);
		}
	}
	return (count);
}
