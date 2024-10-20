/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:20:28 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/15 21:05:43 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	overwrite_env(char *name, char *value)
{
	t_envlist	*env;
	char		*tmp;
	int  flag;

	tmp = NULL;
	flag = 0;
	env = g_sh->envlst;
	if (!name || !value)
		return (free(value), free(name), EXIT_FAILURE);
	while (env != NULL)
	{
		if (ft_strcmp(env->name, name))
		{
			tmp = env->value;
			env->value = value;
			flag = 1;
			break ;
		}
		env = env->next;
	}
	if (flag == 0)
		free(name);
	free(tmp);
	free(name);
	return (EXIT_SUCCESS);
}

void	ft_setenv(char *name, char *value)
{
	t_envlist	*var;

	var = NULL;
	if (name == NULL)
		return ;
	if (env_exist(name) && value != NULL)
	{
		if (overwrite_env(name, value))
			return ;
	}
	else if (env_exist(name) && value == NULL)
	{
		free(name);
		return ;
	}
	else
	{
		var = lstnew_env(name, value);
		if (var == NULL)
			return ;
		lstadd_env_back(&g_sh->envlst, var);
	}
}
