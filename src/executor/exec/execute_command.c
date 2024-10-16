/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:01:51 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/14 01:20:49 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	parent_routine(pid_t pid, int *status, t_pair *pl)
{
	if ((g_sh->args == NULL && pl && !(pl->right) && !(pl->left)) || (g_sh->args
			&& pl && !(pl->right) && !(pl->left)
			&& !(is_built_in(g_sh->args[0]))))
	{
		waitpid(pid, status, 0);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status) && WTERMSIG(*status) == 2 && WTERMSIG(*status) == 3)
		{
			*status = WTERMSIG(*status) + 128;
		   printf("\n");
		}
	}
	return (*status);
}

static void	duppp(t_pair *pl, int pipefd[3])
{
	if (pl->right)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (pl->left)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	if (pipefd && pipefd[2])
		close(pipefd[2]);
}

static int	sth_failed(char *cmd_path, char **e)
{
	free(cmd_path);
	free_strarray(e);
	return (free_mem(1));
}

static int	child_routine(t_ast_node *node, t_pair *pl, int pipefd[3],
		char **cmd_path)
{
	char	**e;

	e = env_tostrarray();
	if (g_sh->args && get_commandpath(cmd_path, g_sh->args[0]))
		exit(sth_failed(*cmd_path, e));
	if (redirect(node, &(pl->left), &(pl->right)) != 0)
		exit(redirect_fail2(*cmd_path, pipefd, e));
	if (g_sh->args == NULL || g_sh->args[0] == NULL)
	{
		free_strarray(e);
		free_mem(1);
		exit(EXIT_SUCCESS);
	}
	duppp(pl, pipefd);
	if (g_sh->args && pre_exec_errors(g_sh->args[0], *cmd_path))
		exit(sth_failed(*cmd_path, e));
	if (!*cmd_path || execve(*cmd_path, g_sh->args, e) < 0)
	{
		free_strarray(e);
		exit(free_mem(1));
	}
	free_strarray(e);
	free(*cmd_path);
	exit(free_mem(1));
}

int	execute_command(t_ast_node *node, t_pair *pl, int pipefd[3],
		pid_t *last_pid)
{
	int		status;
	char	*cmd_path;
	pid_t	pid;

	cmd_path = NULL;
	g_sh->args = lst_tostrarray(node->u_data.s_childs.left->u_data.arg_list);
	status = 0;
	if (g_sh->args && built_ins(node, pl, pipefd))
		return (g_sh->ex_status);
	pid = fork();
	if (last_pid)
		*last_pid = pid;
	if (pid > 0)
		return (parent_routine(pid, &status, pl));
	else if (pid == 0)
	{
		handle_signals(CHILD);
		exit(child_routine(node, pl, pipefd, &cmd_path));
	}
	else
		return (EXIT_FAILURE);
}
