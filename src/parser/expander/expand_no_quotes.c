/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:06:13 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 12:07:34 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	process_tok(t_token *tok, t_token **toklst);

t_token	*expand_noquotes(t_token **head)
{
	t_token	*toklst;
	t_token	*tok;
	int		flag;
	t_token	*tmp;

	toklst = NULL;
	tok = *head;
	flag = 0;
	while (tok != NULL)
	{
		if (flag == 0 && (is_schar(tok->lexem) == 0 || tok->lexem == O_FILE)
			&& tok->lexem != DELIMITER)
			process_tok(tok, &toklst);
		else
		{
			tmp = ft_lstnew_token(ft_strdup(tok->content));
			tmp->lexem = tok->lexem;
			ft_lstadd_token_back(&toklst, tmp);
		}
		tok = tok->next;
	}
	tokens_lstclear(head);
	return (toklst);
}

static void	process_tok(t_token *tok, t_token **toklst)
{
	char	*str;
	t_token	*tmp;

	tmp = NULL;
	if (tok->lexem == STRING || tok->lexem == CMD || tok->lexem == O_FILE
		|| tok->lexem == ARG)
	{
		str = expand_string(tok->content);
		tmp = split_tokens(str);
		if (tok->lexem == O_FILE && (tmp == NULL || toklst_size(tmp) > 1))
		{
			tokens_lstclear(&tmp);
			tmp = ft_lstnew_token(ft_strdup(tok->content));
			tmp->lexem = AMBIGUOUS;
			ft_lstadd_token_back(toklst, tmp);
		}
		else if (tmp != NULL)
		{
			tmp->lexem = tok->lexem;
			ft_lstadd_token_back(toklst, tmp);
		}
		free(str);
	}
}
