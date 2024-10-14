/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:01:54 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/14 02:33:58 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	start_of_piping(t_ast_node *node, int (*clonefds)[3])
{
	int	status;

	status = 0;
	if (pipe(g_sh->pipefd) == -1)
		return (EXIT_FAILURE);
	(*clonefds)[0] = g_sh->pipefd[0];
	(*clonefds)[1] = g_sh->pipefd[1];
	(*clonefds)[2] = g_sh->pipefd[0];
	if (node->u_data.s_childs.left->type == COMMAND)
		execute_command(node->u_data.s_childs.left, \
		(t_pair[]){{0, 1}}, *clonefds, NULL);
	if (node->u_data.s_childs.left->type == GROUP_NODE)
		execute_group(node->u_data.s_childs.left, \
		(t_pair[]){{0, 1}}, *clonefds, NULL);
	return (status);
}

int	middle_of_piping(t_ast_node *node, int (*clonefds)[3])
{
	int	status;

	status = 0;
	close((*clonefds)[1]);
	pipe(g_sh->pipefd);
	(*clonefds)[1] = g_sh->pipefd[1];
	(*clonefds)[2] = g_sh->pipefd[0];
	if (node->u_data.s_childs.left->type == COMMAND)
		execute_command(node->u_data.s_childs.left, \
		(t_pair[]){{1, 1}}, *clonefds, NULL);
	if (node->u_data.s_childs.left->type == GROUP_NODE)
		execute_group(node->u_data.s_childs.left, \
		(t_pair[]){{1, 1}}, *clonefds, NULL);
	close((*clonefds)[0]);
	(*clonefds)[0] = g_sh->pipefd[0];
	(*clonefds)[2] = 0;
	return (status);
}

pid_t	end_of_piping(t_ast_node *node, int (*clonefds)[3])
{
	pid_t	pid;

	pid = 0;
	close((*clonefds)[1]);
	if (node->type == COMMAND)
		execute_command(node, (t_pair[]){{1, 0}}, *clonefds, &pid);
	if (node->type == GROUP_NODE)
		execute_group(node, (t_pair[]){{1, 0}}, *clonefds, &pid);
	close((*clonefds)[0]);
	return (pid);
}

int	waiting(pid_t last_pid, int childs)
{
	int	last_exit_status;
	int	exit_status;
	int	printed;

	last_exit_status = 0;
	exit_status = 0;
	printed = 0;
	while (childs)
	{
		if (wait(&exit_status) == last_pid)
			last_exit_status = exit_status;
		if (WIFSIGNALED(exit_status) && (WTERMSIG(exit_status) == SIGINT
				|| WTERMSIG(exit_status) == SIGQUIT) && !printed)
			printed = ft_printf("\n");
		childs--;
	}
	if (WIFEXITED(last_exit_status))
		last_exit_status = WEXITSTATUS(last_exit_status);
	else if (WIFSIGNALED(last_exit_status))
		last_exit_status = WTERMSIG(last_exit_status) + 128;
	return (last_exit_status);
}

int	execute_pipeline(t_ast_node *node)
{
	int		childs;
	int		clonefds[3];
	pid_t	pid;

	clonefds[2] = 0;
	start_of_piping(node, &clonefds);
	node = node->u_data.s_childs.right;
	childs = 2;
	free_strarray(g_sh->args);
	g_sh->args = NULL;
	while (node != NULL && node->type == PIPELINE)
	{
		middle_of_piping(node, &clonefds);
		node = node->u_data.s_childs.right;
		childs++;
		free_strarray(g_sh->args);
		g_sh->args = NULL;
	}
	clonefds[0] = g_sh->pipefd[0];
	pid = end_of_piping(node, &clonefds);
	return (waiting(pid, childs));
}
