/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:55:31 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 13:55:58 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void		insert_wc_tok(t_token *head, t_token **exp_tok,
					t_token **newtoklst);
static int		return_expand(t_token *old_tok, t_token **new_tok);
static t_token	*args_to_toks(t_argument *args);
// static int manage_flag(t_token *tok, int flag);
static int		is_quoted(char *str);

int	expand_wildcard(t_token **toks)
{
	t_token	*exp_tok;
	t_token	*newtoklst;
	t_token	*toks_head;

	toks_head = *toks;
	exp_tok = NULL;
	newtoklst = NULL;
	while (toks_head != NULL)
	{
		if (return_expand(toks_head, &exp_tok))
			return (EXIT_FAILURE);
		insert_wc_tok(toks_head, &exp_tok, &newtoklst);
		toks_head = toks_head->next;
	}
	tokens_lstclear(toks);
	*toks = newtoklst;
	return (EXIT_SUCCESS);
}

static void	insert_wc_tok(t_token *head, t_token **exp_tok, t_token **newtoklst)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(*exp_tok))
	{
		tmp = ft_lstnew_token(ft_strdup(head->content));
		tmp->lexem = head->lexem;
		ft_lstadd_token_back(newtoklst, tmp);
	}
	else
	{
		if (head->lexem == O_FILE && toklst_size(*exp_tok) > 1)
		{
			tokens_lstclear(exp_tok);
			tmp = ft_lstnew_token(ft_strdup(head->content));
			tmp->lexem = AMBIGUOUS;
			ft_lstadd_token_back(newtoklst, tmp);
		}
		else
			ft_lstadd_token_back(newtoklst, *exp_tok);
		*exp_tok = NULL;
	}
}

static int	return_expand(t_token *old_tok, t_token **new_tok)
{
	t_argument	*args;

	args = NULL;
	if (!is_quoted(old_tok->content) && ft_strchr(old_tok->content, '*'))
	{
		old_tok->content = remove_quote(old_tok->content);
		args = wildcard_core(old_tok->content);
		if (args != NULL)
		{
			*new_tok = args_to_toks(args);
			if (*new_tok == NULL)
			{
				clear_argslst(&args);
				return (EXIT_FAILURE);
			}
		}
	}
	clear_argslst(&args);
	return (EXIT_SUCCESS);
}

static int	is_quoted(char *str)
{
	size_t	itr;
	int		flag;
	char	quote;

	itr = 0;
	flag = 0;
	while (str[itr])
	{
		if (flag == 0 && (str[itr] == DQUOTE || str[itr] == QUOTE))
		{
			quote = str[itr];
			flag = 1;
		}
		else if (flag == 1 && str[itr] == quote)
			flag = 0;
		if (str[itr] == '*' && flag == 1)
			return (1);
		itr++;
	}
	return (0);
}

static t_token	*args_to_toks(t_argument *args)
{
	t_token	*tok;
	t_token	*tmp_tok;

	tok = NULL;
	tmp_tok = NULL;
	while (args != NULL)
	{
		tmp_tok = ft_lstnew_token(ft_strdup(args->content));
		if (tmp_tok == NULL)
			return (NULL);
		ft_lstadd_token_back(&tok, tmp_tok);
		args = args->next;
	}
	return (tok);
}

// static int manage_flag(t_token *tok, int flag)
// {
//     if (flag == 0 && tok->lexem == CMD
//         && ft_strcmp(tok->content, "export"))
//         flag = 1;
//     else if (flag == 1 && is_schar(tok->lexem) != 0)
//         flag = 0;
//     return (flag);
// }