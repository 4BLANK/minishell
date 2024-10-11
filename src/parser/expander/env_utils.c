/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:42:12 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/11 01:18:48 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*getenv_name(char *variable)
{
	char	*var_name;
	size_t	i;

	i = 0;
	if (variable == NULL)
		return (NULL);
	while (variable[i] && variable[i] != '=')
		i++;
	var_name = ft_substr(variable, 0, i);
	return (var_name);
}

char	*getenv_value(char *variable)
{
	char	*value;
	size_t	start;

	start = 0;
	value = NULL;
	if (variable == NULL)
		return (NULL);
	while (variable[start] && variable[start] != '=')
		start++;
	if (start == ft_strlen(variable))
		return (NULL);
	value = ft_substr(variable, start + 1, ft_strlen(variable) - start);
	value = remove_quote(value);
	return (value);
}

void	print_env(t_envlist *envlst)
{
	while (envlst != NULL)
	{
		if (envlst->value == NULL)
			ft_printf("declare -x %s\n", envlst->name);
		else
			ft_printf("declare -x %s=\"%s\"\n", envlst->name, envlst->value);
		envlst = envlst->next;
	}
}

char	*ft_getenv(char *name)
{
	t_envlist	*lst;

	lst = sh->envlst;
	if (name == NULL || name[0] == '\0')
		return (NULL);
	while (lst != NULL)
	{
		if (ft_strcmp(name, lst->name))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

t_envlist	*init_envlist(char **env)
{
	t_envlist	*envlst;
	t_envlist	*tmp;
	char *name;
	char *value;
	size_t		i;

	i = 0;
	envlst = NULL;
	tmp = NULL;
	while (env[i])
	{
		name = getenv_name(env[i]);
		value = getenv_value(env[i]);
		tmp = lstnew_env(name, value);
		lstadd_env_back(&envlst, tmp);
		i++;
	}
	return (envlst);
}
