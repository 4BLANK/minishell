/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:56:30 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/13 23:46:36 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_name(char *str, int itr)
{
	char	*env_name;
	int		i;
	int		len;

	i = itr;
	len = 0;
	while (str[i] && !is_space(str[i]) && (ft_isalpha(str[i])
			|| ft_isdigit(str[i])))
	{
		len++;
		i++;
	}
	env_name = ft_substr(str, itr, len);
	return (env_name);
}

char	*expand_pid_or_exit(char *str, char curchr, char nextchr)
{
	char	*tmp;
	char	*new_str;

	tmp = NULL;
	new_str = NULL;
	if (curchr && nextchr == DOLLAR_SIGN)
	{
		tmp = ft_itoa((int)getpid());
		new_str = concat(str, tmp, 0);
	}
	else if (curchr && nextchr == QUESTION_MARK)
	{
		tmp = ft_itoa(g_sh->ex_status);
		new_str = concat(str, tmp, 0);
	}
	free(tmp);
	return (new_str);
}

size_t	toklst_size(t_token *toks)
{
	size_t	len;

	len = 0;
	while (toks != NULL)
	{
		len++;
		toks = toks->next;
	}
	return (len);
}

int	expander(t_token **tokens)
{
	t_token	*tmp;

	tmp = (*tokens);
	while ((*tokens) != NULL)
	{
		if ((*tokens)->lexem == STRING || (*tokens)->lexem == ARG
			|| (*tokens)->lexem == CMD || (*tokens)->lexem == O_FILE)
			(*tokens)->content = expand_token((*tokens)->content);
		*tokens = (*tokens)->next;
	}
	*tokens = tmp;
	lexer(*tokens);
	return (EXIT_SUCCESS);
}

int	expander_core(t_token **toklst)
{
	*toklst = expand_noquotes(toklst);
	if (expander(toklst))
		return (EXIT_FAILURE);
	if (expand_wildcard(toklst))
		return (EXIT_FAILURE);
	if (rm_token_quotes(*toklst))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
