/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extra_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:42:19 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/07 14:43:13 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_envlist	*lstnew_env(char *name, char *value)
{
	t_envlist	*token;

	token = (t_envlist *)malloc(sizeof(t_envlist));
	if (token == NULL)
		return (NULL);
	token->name = name;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	lstadd_env_back(t_envlist **lst, t_envlist *newenv)
{
	t_envlist	*token;

	if (newenv != NULL)
	{
		if (*lst == NULL)
			*lst = newenv;
		else
		{
			token = *lst;
			while (token->next != NULL)
				token = token->next;
			token->next = newenv;
		}
	}
}

void	distroy_envlst(t_envlist **envlst)
{
	t_envlist	*node;
	t_envlist	*next;

	if (envlst && *envlst)
	{
		node = *envlst;
		while (node != NULL)
		{
			next = node->next;
			free(node->name);
			free(node->value);
			free(node);
			node = next;
		}
		*envlst = NULL;
	}
}
