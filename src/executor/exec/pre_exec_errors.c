/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:02:04 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 23:46:17 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_dir0(char *pwd)
{
	DIR	*dir;

	dir = opendir(pwd);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	on_slash(char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (is_dir0(cmd))
		{
			printerr(cmd, 1);
			g_sh->ex_status = 126;
		}
		else
		{
			if (access(cmd, X_OK))
			{
				printerr(cmd, 2);
				g_sh->ex_status = 126;
			}
		}
	}
	else
	{
		printerr(cmd, 3);
		g_sh->ex_status = 127;
	}
}

int	pre_exec_errors(char *cmd, char *cmd_path)
{
	g_sh->ex_status = 0;
	if (has_slash(cmd))
		on_slash(cmd);
	else
	{
		if (!ft_getenv("PATH") || ft_getenv("PATH")[0] == '\0')
			return (line_rm(cmd));
		else if (!cmd_path || access(cmd_path, X_OK))
		{
			printerr(cmd, 4);
			g_sh->ex_status = 127;
		}
	}
	return (g_sh->ex_status);
}
