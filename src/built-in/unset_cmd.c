/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:29:59 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/06 13:30:00 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	remove_envnode(t_envlist **env, size_t pos);
static int	dalete_var(t_envlist *env, char *name);
static void	delete_from_middle(size_t pos, t_envlist *tmp);

int	unset_cmd(char **args)
{
	size_t	i;

	i = 1;
	if (args == NULL)
		return (EXIT_FAILURE);
	if (str_arraysize(args) == 1)
		return (EXIT_SUCCESS);
	while (args[i])
	{
		if (env_exist(args[i]))
			dalete_var(sh->envlst, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	remove_envnode(t_envlist **env, size_t pos)
{
	t_envlist	*tmp;

	if (*env == NULL)
		return (EXIT_SUCCESS);
	tmp = *env;
	if (pos == 0)
	{
		*env = tmp->next;
		free(tmp->name);
		free(tmp);
		tmp = NULL;
		return (EXIT_SUCCESS);
	}
	else
		delete_from_middle(pos, tmp);
	return (EXIT_SUCCESS);
}

static void	delete_from_middle(size_t pos, t_envlist *tmp)
{
	t_envlist	*node;
	size_t		itr;

	node = NULL;
	itr = 0;
	while (tmp != NULL && itr < pos - 1)
	{
		tmp = tmp->next;
		itr++;
	}
	if (tmp == NULL || tmp->next == NULL)
		return ;
	node = tmp->next->next;
	free((tmp->next)->name);
	free(tmp->next);
	tmp->next = node;
	tmp = NULL;
	return ;
}

static int	dalete_var(t_envlist *env, char *name)
{
	size_t		pos;
	t_envlist	*lst;

	pos = 0;
	lst = env;
	while (lst != NULL)
	{
		if (ft_strncmp(name, lst->name, sizeof(name)) == 0)
		{
			remove_envnode(&sh->envlst, pos);
			break ;
		}
		pos++;
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
