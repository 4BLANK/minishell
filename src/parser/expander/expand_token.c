/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:53:04 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 21:31:20 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	expand_token_core(char **new_str, char *str, size_t *i);
static void	expand_env_var(char *str, char **new_str, size_t *i);


void	check_tmp(char *tmp, char **newstr, size_t *itr)
{
	if (tmp != NULL)
	{
		*newstr = tmp;
		(*itr)++;
	}
}

char	*expand_heredoc(char *str)
{
	size_t	itr;
	char	*newstr;
	char	*tmp;

	itr = 0;
	newstr = NULL;
	while (str[itr])
	{
		if (str[itr] == DOLLAR_SIGN)
		{
			if (str[itr + 1] && str[itr + 1] == QUESTION_MARK)
			{
				tmp = expand_pid_or_exit(newstr, str[itr], str[itr + 1]);
				check_tmp(tmp, &newstr, &itr);
			}
			else
				expand_env_var(str, &newstr, &itr);
		}
		else
			newstr = concat(newstr, str + itr, 1);
		itr++;
	}
	return (newstr);
}

char	*expand_string(char *str)
{
	size_t	itr;
	char	*new_str;
	char	quote_type;
	int		quote_flag;

	itr = 0;
	quote_flag = 0;
	new_str = NULL;
	while (str[itr])
	{
		if (quote_flag == 0 && (str[itr] == QUOTE || str[itr] == DQUOTE))
		{
			quote_flag = 1;
			quote_type = str[itr];
		}
		else if (quote_flag == 1 && str[itr] == quote_type)
			quote_flag = 0;
		if (quote_flag == 0 && str[itr] == DOLLAR_SIGN && str[itr + 1]
			&& (str[itr + 1] == QUESTION_MARK || ft_isalpha(str[itr + 1])))
			expand_token_core(&new_str, str, &itr);
		else
			new_str = concat(new_str, str + itr, 1);
		itr++;
	}
	return (new_str);
}

char	*expand_token(char *str)
{
	char	*new_str;
	int		fg;
	char	c;
	size_t	i;

	i = 0;
	fg = 0;
	new_str = NULL;
	while (str[i])
	{
		if (fg == 0 && (str[i] == QUOTE || str[i] == DQUOTE))
		{
			fg = 1;
			c = str[i];
		}
		else if (fg == 1 && str[i] == c)
			fg = 0;
		if (fg == 1 && str[i] == DOLLAR_SIGN && c != QUOTE && (str[i + 1]
				&& (str[i + 1] == QUESTION_MARK || ft_isalpha(str[i + 1]))))
			expand_token_core(&new_str, str, &i);
		else
			new_str = concat(new_str, str + i, 1);
		i++;
	}
	return (free(str), new_str);
}

static void	expand_token_core(char **new_str, char *str, size_t *i)
{
	char	*tmp;

	tmp = expand_pid_or_exit(*new_str, str[*i], str[*i + 1]);
	if (tmp != NULL)
	{
		*new_str = tmp;
		(*i)++;
	}
	else
		expand_env_var(str, new_str, i);
}

static void	expand_env_var(char *str, char **new_str, size_t *i)
{
	char	*envname;
	char	*value;

	value = NULL;
	envname = get_name(str, *i + 1);
	value = ft_strdup(ft_getenv(envname));
	*new_str = concat(*new_str, value, 0);
	*i = *i + ft_strlen(envname);
	free(value);
	free(envname);
}
