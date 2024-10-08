/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:02:49 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 21:33:43 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	tokens_lstclear(t_token **lst)
{
	t_token	*node;
	t_token	*next;

	if (lst && *lst)
	{
		node = *lst;
		while (node != NULL)
		{
			next = node->next;
			free(node->content);
			free(node);
			node = next;
		}
		*lst = NULL;
	}
}

int	rm_token_quotes(t_token *tokenlst)
{
	while (tokenlst != NULL)
	{
		tokenlst->content = remove_quote(tokenlst->content);
		if (tokenlst->content == NULL)
			return (print_error("malloc_error", 2));
		tokenlst = tokenlst->next;
	}
	return (EXIT_SUCCESS);
}

t_token	*ft_lstnew_token(void *content)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->content = content;
	token->lexem = STRING;
	token->next = NULL;
	return (token);
}
// int	check_quote(char c, int *flag, char *quote)
// {
// 	if (*flag == 0 && (c == QUOTE || c == DQUOTE))
// 	{
// 		*flag = 1;
// 		*quote = c;
// 	}
// 	else if (*flag == 1 && c == *quote)
// 		*flag = 0;
// 	return (*flag);
// }
int	check_quote(char c, int *flag, char *quote)
{
	int	result;

	result = 0;
	if (*flag == 0 && (c == QUOTE || c == DQUOTE))
	{
		*flag = 1;
		*quote = c;
		result = 1;
	}
	else if (*flag == 1 && c == *quote)
	{
		result = 1;
		*flag = 0;
	}
	return (result);
}
