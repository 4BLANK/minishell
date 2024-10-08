/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:48:01 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 14:40:05 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_argsadd_back(t_argument **lst, t_argument *new)
{
	t_argument	*node;

	if (new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			node = *lst;
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = new;
		}
	}
}

t_argument	*ft_argsnew(void *content)
{
	t_argument	*node;

	node = (t_argument *)malloc(sizeof(t_argument));
	if (node == NULL)
		return (0);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	clear_argslst(t_argument **lst)
{
	t_argument	*node;
	t_argument	*next;

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

int	is_schar(t_lexeme lexem)
{
	if (lexem == O_REDIRECTION || lexem == I_REDIRECTION || lexem == HEREDOC
		|| lexem == APPEND)
		return (1);
	else if (lexem == PIPE || lexem == AND || lexem == OR || lexem == OPEN_P
		|| lexem == CLOSE_P)
		return (2);
	return (0);
}
