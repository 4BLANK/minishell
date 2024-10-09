#include "../../../includes/minishell.h"

static void	child_routine(t_ast_node *node, t_pair *pl, int pipefd[2])
{
	if (redirect(node, &(pl->left), &(pl->right)))
		exit(EXIT_FAILURE);
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
	kickoff(node->data.childs.left);
	exit(free_mem(1));
}

int	execute_group(t_ast_node *node, t_pair *pl, int pipefd[3], pid_t *last_pid)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (last_pid)
		*last_pid = pid;
	if (pid > 0 && (!pl->right && !pl->left))
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			ft_printf("\n");
		return (status);
	}
	else if (pid == 0)
		child_routine(node, pl, pipefd);
	else
		status = EXIT_FAILURE;
	return (status);
}
