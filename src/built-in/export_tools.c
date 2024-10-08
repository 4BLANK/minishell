/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:20:28 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/06 13:23:07 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	overwrite_env(char *name, char *value)
{
	t_envlist	*env;
	char		*tmp;

	tmp = NULL;
	env = sh->envlst;
	if (!name || !value)
		return (EXIT_FAILURE);
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, sizeof(name)) == 0)
		{
			tmp = env->value;
			env->value = value;
			break ;
		}
		env = env->next;
	}
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
	value = remove_quote(value);
	if (env_exist(name) && value != NULL)
	{
		if (overwrite_env(name, value))
			return ;
	}
	else if (env_exist(name) && value == NULL)
		return ;
	else
	{
		var = lstnew_env(name, value);
		if (var == NULL)
			return ;
		lstadd_env_back(&sh->envlst, var);
	}
}
