/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:14:18 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/08 18:38:16 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_dir(char *pwd)
{
	DIR	*dir;

	dir = NULL;
	if (access(pwd, F_OK) != -1)
	{
		dir = opendir(pwd);
		if (dir != NULL)
		{
			closedir(dir);
		}
		else
		{
			ft_error("cd", pwd, "Not a directory\n");
			return (-2);
		}
	}
	else
	{
		ft_error("cd", pwd, "No such file or directory\n");
		return (-1);
	}
	return (1);
}

int	cd_cmd(char **args)
{
	char	*pwd;
	char	*home;

	home = NULL;
	if (str_arraysize(args) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	pwd = args[1];
	if (pwd == NULL)
	{
		home = ft_getenv("HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		pwd = home;
	}
	if (is_dir(pwd) != 1 || chdir(pwd))
		return (EXIT_FAILURE);
	pwd = getcwd(NULL, 0);
	if (overwrite_env(ft_strdup("PWD"), ft_strdup(pwd)))
	{
		return (free(home), EXIT_FAILURE);
		free(pwd);
	}
	free(pwd);
	return (free(home), EXIT_SUCCESS);
}
