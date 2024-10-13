/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:02:00 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 03:02:53 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	printerr(char *str, int flag)
{
	ft_putstr_fd("chnghl o mnghl: ", 2);
	ft_putstr_fd(str, 2);
	if (flag == 1)
		ft_putstr_fd(": is a directory\n", 2);
	if (flag == 2)
		ft_putstr_fd(": permission denied\n", 2);
	if (flag == 3)
		ft_putstr_fd(": no such file or directory\n", 2);
	if (flag == 4)
		ft_putstr_fd(": command not found\n", 2);
}

void	close_save(int save[2])
{
	dup2(save[0], STDIN_FILENO);
	close(save[0]);
	dup2(save[1], STDOUT_FILENO);
	close(save[1]);
}

int	redirect_fail(int pipefd[3], int save[2])
{
	dup2(save[0], STDIN_FILENO);
	close(save[0]);
	dup2(save[1], STDOUT_FILENO);
	close(save[1]);
	if (pipefd && pipefd[1])
		close(pipefd[1]);
	if (pipefd && pipefd[0])
		close(pipefd[0]);
	if (pipefd && pipefd[2])
		close(pipefd[2]);
	return (EXIT_FAILURE);
}

int	line_rm(char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (is_dir0(cmd))
		{
			printerr(cmd, 1);
			sh->ex_status = 126;
		}
		else
		{
			if (access(cmd, X_OK))
			{
				printerr(cmd, 2);
				sh->ex_status = 126;
			}
			return (0);
		}
	}
	else
	{
		printerr(cmd, 3);
		sh->ex_status = 127;
	}
	return (sh->ex_status);
}

int	redirect_fail2(char *cmd_path, int pipefd[3], char **e)
{
	if (pipefd && pipefd[1])
		close(pipefd[1]);
	if (pipefd && pipefd[0])
		close(pipefd[0]);
	if (pipefd && pipefd[2])
		close(pipefd[2]);
	free(cmd_path);
	free_strarray(e);
	return (free_mem(1));
}
