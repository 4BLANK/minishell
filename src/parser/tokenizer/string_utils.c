/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:02:55 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 18:48:51 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	toggle_quotes(char c, int flag)
{
	if (flag == 0 && (c == DQUOTE || c == QUOTE))
		flag = 1;
	else if (flag == 1 && (c == DQUOTE || c == QUOTE))
		flag = 0;
	return (flag);
}

void	process_character(char *newline, char *line, size_t *i, size_t *j)
{
	if (line[*i] == CPAREN || line[*i] == OPAREN)
	{
		newline[(*j)++] = ' ';
		newline[*j] = line[*i];
		newline[++(*j)] = ' ';
	}
	else if (line[*i] == AMPERSAND)
	{
		if (*i != 0 && line[*i - 1] != line[*i] && line[*i + 1] \
			&& line[*i + 1] == line[*i])
			newline[(*j)++] = ' ';
		newline[*j] = line[*i];
		if (line[*i + 1] && line[*i + 1] != line[*i] && (*i != 0 \
			&& line[*i - 1] == line[*i]))
			newline[++(*j)] = ' ';
	}
	else
	{
		if ((*i != 0 && line[*i - 1] != line[*i]))
			newline[(*j)++] = ' ';
		newline[*j] = line[*i];
		if (line[*i + 1] && line[*i + 1] != line[*i])
			newline[++(*j)] = ' ';
	}
}

char	*expand_line(char *line, size_t len)
{
	size_t	i;
	size_t	j;
	int		flag;
	char	*newline;

	flag = 0;
	i = 0;
	j = 0;
	newline = (char *)malloc(sizeof(char) * len);
	if (newline == NULL)
		return (NULL);
	while (line[i])
	{
		flag = toggle_quotes(line[i], flag);
		if (flag == 0 && schar_detected(line[i]))
			process_character(newline, line, &i, &j);
		else
			newline[j] = line[i];
		j++;
		i++;
	}
	newline[j] = '\0';
	return (newline);
}

int	get_expanded_line(char **line)
{
	char	*newline;
	size_t	len;

	len = 0;
	if (*line == NULL)
		return (EXIT_FAILURE);
	len = ft_strlen(*line) + (count_schar(*line) * 2) + 1;
	newline = expand_line(*line, len);
	if (newline == NULL)
		return (EXIT_FAILURE);
	free(*line);
	*line = newline;
	return (EXIT_SUCCESS);
}

int	modify_line(char **line)
{
	if (get_expanded_line(line))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
