/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:01:47 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 23:43:48 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static size_t	lstsize(t_argument *lst)
{
	int			count;
	t_argument	*current;

	count = 0;
	current = lst;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**lst_tostrarray(t_argument *head)
{
	size_t	count;
	char	**strarray;
	int		i;

	i = 0;
	count = lstsize(head);
	if (!(count))
		return (NULL);
	strarray = (char **)ft_calloc(sizeof(char *), (count + 1));
	if (strarray == NULL)
		return (NULL);
	while (head != NULL)
	{
		strarray[i] = ft_strdup(head->content);
		if (strarray[i] == NULL)
			return (NULL);
		head = head->next;
		i++;
	}
	strarray[i] = NULL;
	return (strarray);
}

char	*get_element(char *name, char *value)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

size_t	envsize(void)
{
	size_t		count;
	t_envlist	*tmp;

	count = 0;
	tmp = g_sh->envlst;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**env_tostrarray(void)
{
	size_t		count;
	char		**strarray;
	t_envlist	*head;
	size_t		i;

	i = 0;
	head = g_sh->envlst;
	count = envsize();
	if (!(count))
		return (NULL);
	strarray = (char **)ft_calloc(sizeof(char *), (count + 1));
	if (strarray == NULL)
		return (NULL);
	while (head != NULL)
	{
		strarray[i] = get_element(head->name, head->value);
		if (strarray[i] == NULL)
			return (NULL);
		head = head->next;
		i++;
	}
	strarray[i] = NULL;
	return (strarray);
}
