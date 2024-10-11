#include "../../../includes/minishell.h"

int	start_of_piping(t_ast_node *node, int (*clonefds)[3])
{
	int	status;

	status = 0;
	if (pipe(sh->pipefd) == -1)
		return (EXIT_FAILURE);
	(*clonefds)[0] = sh->pipefd[0];
	(*clonefds)[1] = sh->pipefd[1];
	(*clonefds)[2] = sh->pipefd[0];
	if (node->data.childs.left->type == COMMAND)
		execute_command(node->data.childs.left, (t_pair[]){{0, 1}}, *clonefds,
			NULL);
	if (node->data.childs.left->type == GROUP_NODE)
		execute_group(node->data.childs.left, (t_pair[]){{0, 1}}, *clonefds,
			NULL);
	return (status);
}

int	middle_of_piping(t_ast_node *node, int (*clonefds)[3])
{
	int	status;

	status = 0;
	close((*clonefds)[1]);
	pipe(sh->pipefd);
	(*clonefds)[1] = sh->pipefd[1];
	(*clonefds)[2] = sh->pipefd[0];
	if (node->data.childs.left->type == COMMAND)
		execute_command(node->data.childs.left, (t_pair[]){{1, 1}}, *clonefds,
			NULL);
	if (node->data.childs.left->type == GROUP_NODE)
		execute_group(node->data.childs.left, (t_pair[]){{1, 1}}, *clonefds,
			NULL);
	close((*clonefds)[0]);
	(*clonefds)[0] = sh->pipefd[0];
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
  int printed;

	last_exit_status = 0;
	exit_status = 0;
  printed = 0;
	while (childs)
	{
		if (wait(&exit_status) == last_pid)
			last_exit_status = exit_status;
    if (WIFSIGNALED(exit_status) && !printed)
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
	node = node->data.childs.right;
	childs = 2;
	if (sh->args)
		free_strarray(sh->args);
	while (node != NULL && node->type == PIPELINE)
	{
		middle_of_piping(node, &clonefds);
		node = node->data.childs.right;
		childs++;
		if (sh->args)
			free_strarray(sh->args);
	}
	clonefds[0] = sh->pipefd[0];
	pid = end_of_piping(node, &clonefds);
	return (waiting(pid, childs));
}
