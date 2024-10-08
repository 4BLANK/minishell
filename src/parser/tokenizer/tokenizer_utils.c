/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:03:38 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 20:05:39 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	print_error(char *error, int exit_code)
{
	ft_putstr_fd(error, 2);
	return (exit_code);
}

void	print_lst(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens != NULL)
	{
		printf("%d -> [%s | %s] \n", i++, tokens->content,
			lexs_type[tokens->lexem]);
		tokens = tokens->next;
	}
}

t_token	*ft_lstlast_token(t_token *lst)
{
	t_token	*node;

	node = NULL;
	while (lst)
	{
		if (lst->next == NULL)
			node = lst;
		lst = lst->next;
	}
	return (node);
}

void	ft_lstadd_token_back(t_token **lst, t_token *new)
{
	t_token	*token;

	if (new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			token = *lst;
			while (token->next != NULL)
				token = token->next;
			token->next = new;
		}
	}
}

t_token	*new_token(void *content, t_lexeme lex)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (0);
	token->content = content;
	token->lexem = lex;
	token->next = NULL;
	return (token);
}
