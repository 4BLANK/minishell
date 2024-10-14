/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:01:39 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/14 00:53:28 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_built_in(char *str)
{
	return (!(ft_strncmp(str, "pwd", 4)) || !(ft_strncmp(str, "echo", 5))
		|| !(ft_strncmp(str, "exit", 5)) || !(ft_strncmp(str, "env", 4))
		|| !(ft_strncmp(str, "export", 7)) || !(ft_strncmp(str, "cd", 3))
		|| !(ft_strncmp(str, "unset", 6)));
}

static void	type_shi(int save[2])
{
	if (!ft_strncmp(g_sh->args[0], "pwd", 3))
		g_sh->ex_status = pwd_cmd(g_sh->args);
	if (!ft_strncmp(g_sh->args[0], "echo", 4))
		g_sh->ex_status = echo(g_sh->args);
	if (!ft_strncmp(g_sh->args[0], "env", 3))
		g_sh->ex_status = env_cmd();
	if (!ft_strncmp(g_sh->args[0], "exit", 4))
	{
		dup2(save[0], STDIN_FILENO);
		close(save[0]);
		dup2(save[1], STDOUT_FILENO);
		close(save[1]);
		g_sh->ex_status = exit_cmd(g_sh->args, &(g_sh->ast));
	}
	if (!ft_strncmp(g_sh->args[0], "export", 6))
		g_sh->ex_status = export_cmd(g_sh->args);
	if (!ft_strncmp(g_sh->args[0], "cd", 2))
		g_sh->ex_status = cd_cmd(g_sh->args);
	if (!ft_strncmp(g_sh->args[0], "unset", 5))
		g_sh->ex_status = unset_cmd(g_sh->args);
}

int	execute(t_ast_node *node, t_pair *pl, int pipefd[3])
{
	int	save[2];

	if (!is_built_in(g_sh->args[0]))
		return (0);
	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	if (redirect(node, &(pl->left), &(pl->right)))
		return (redirect_fail(pipefd, save));
	if (pl->right)
		dup2(pipefd[1], STDOUT_FILENO);
	if (pl->left)
		dup2(pipefd[0], STDIN_FILENO);
	if (pipefd && pipefd[0])
		close(pipefd[0]);
	if (pipefd && pipefd[1])
		close(pipefd[1]);
	if (pipefd && pipefd[2])
		close(pipefd[2]);
	type_shi(save);
	close_save(save);
	return (1);
}

int	under_pipes(t_ast_node *node, t_pair *l, int pipefd[3])
{
	int	pid;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, (int *)&(g_sh->ex_status), 0);
		if (WIFEXITED(g_sh->ex_status))
			g_sh->ex_status = WEXITSTATUS(g_sh->ex_status);
		else
		{
			g_sh->ex_status = WTERMSIG(g_sh->ex_status) + 128;
			ft_printf("\n");
		}
		return (1);
	}
	else if (pid == -1)
		exit(EXIT_FAILURE);
	else
	{
		execute(node, l, pipefd);
		exit(free_mem(1));
	}
}

int	built_ins(t_ast_node *node, t_pair *pl, int pipefd[3])
{
	if (is_built_in(g_sh->args[0]) && (pl->right || pl->left))
		return (under_pipes(node, pl, pipefd));
	else if (is_built_in(g_sh->args[0]) && !(pl->right || pl->left))
		return (execute(node, pl, pipefd));
	return (0);
}
