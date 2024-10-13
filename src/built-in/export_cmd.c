/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:19:25 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/12 21:05:03 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	env_exist(char *name)
{
	t_envlist	*lst;

	lst = sh->envlst;
	while (lst != NULL)
	{
		if (!ft_strncmp(lst->name, name, ft_strlen(name)))
			return (true);
		lst = lst->next;
	}
	return (false);
}

int	ft_error(char *cmd, char *arg, char *error)
{
	ft_putstr_fd("changal: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	return (EXIT_FAILURE);
}

int	invalid_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (arg == NULL)
		return (EXIT_FAILURE);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (ft_error("export", arg, "not a valid identifier\n"));
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != '_' && !ft_isalpha(arg[i]) && !ft_isalnum(arg[i]))
			return (ft_error("export", arg, "not a valid identifier\n"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	export_var(char *arg)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (invalid_arg(arg))
		return (EXIT_FAILURE);
	name = getenv_name(arg);
	value = getenv_value(arg);
	if (value == NULL && ft_strlen(name) != ft_strlen(arg))
	{
		value = malloc(1);
		if (value == NULL)
			return (EXIT_FAILURE);
		value[0] = '\0';
	}
	ft_setenv(name, value);
	return (EXIT_SUCCESS);
}

int	export_cmd(char **args)
{
	size_t	i;
	int		status;
	int		ex_status;

	i = 1;
	status = 0;
	ex_status = 0;
	if (str_arraysize(args) == 1)
		print_env(sh->envlst);
	while (args[i] != NULL)
	{
		status = export_var(args[i]);
		if (status != 0)
			ex_status = status;
		i++;
	}
	return (ex_status);
}
