/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_string_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:04:13 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 18:36:56 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] - s2[i] == 0)
		return (true);
	else
		return (false);
}

int	schar_detected(char c)
{
	if (c == CPIPE || c == GREATER || c == LESS || c == AMPERSAND || c == OPAREN
		|| c == CPAREN)
		return (1);
	return (0);
}

size_t	rm_quotelen(char *str)
{
	size_t	len;
	size_t	i;
	int		flag;
	char	quote;

	i = 0;
	flag = 0;
	len = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == QUOTE || str[i] == DQUOTE))
		{
			flag = 1;
			quote = str[i];
		}
		else if (flag == 1 && str[i] == quote)
			flag = 0;
		else
			len++;
		i++;
	}
	return (len);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	*newstr;
	char	quote;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	if (str == NULL)
		return (NULL);
	newstr = malloc(sizeof(char) * (rm_quotelen(str) + 1));
	if (newstr == NULL)
		return (NULL);
	while (str[i])
	{
		if (!check_quote(str[i], &flag, &quote))
			newstr[j++] = str[i];
		i++;
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}
