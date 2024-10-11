#include "../../../includes/minishell.h"

int	parent_routine(pid_t pid, int *status, t_pair *pl)
{
	if ((sh->args == NULL && pl && !(pl->right) && !(pl->left)) 
	|| (sh->args && pl && !(pl->right) && !(pl->left)
		&& !(is_built_in(sh->args[0]))))
	{
		waitpid(pid, status, 0);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		else
		{
      		*status = WTERMSIG(*status) + 128;
			ft_printf("\n");
		}
	}
	
	return (*status);
}

int	child_routine(t_ast_node *node, t_pair *pl, int pipefd[2], char **cmd_path)
{
	handle_signals(CHILD);
	if (sh->args && get_commandpath(cmd_path, sh->args[0]))
		exit(free_mem(1));
	if (redirect(node, &(pl->left), &(pl->right)) != 0)
	{
		if (pipefd && pipefd[1])
			close(pipefd[1]);
		if (pipefd && pipefd[0])
			close(pipefd[0]);
		if (pipefd && pipefd[2])
			close(pipefd[2]);
		exit(free_mem(1));
	}
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
	if (sh->args && pre_exec_errors(sh->args[0], *cmd_path))
		exit(free_mem(1));
	if (!*cmd_path || execv(*cmd_path, sh->args) < 0)
		exit(free_mem(1));
	exit(free_mem(1));
}

int	execute_command(t_ast_node *node, t_pair *pl, int pipefd[2], pid_t *last_pid)
{
	int		status;
	char	*cmd_path;
	pid_t	pid;

	cmd_path = NULL;
	sh->args = lst_tostrarray(node->data.childs.left->data.arg_list);
	status = 0;
	if (sh->args && built_ins(node, pl, pipefd))
		return (sh->ex_status);
	pid = fork();
	if (last_pid)
		*last_pid = pid;
	if (pid > 0)
		return (parent_routine(pid, &status, pl));
	else if (pid == 0)
		exit(child_routine(node, pl, pipefd, &cmd_path));
	return (EXIT_FAILURE);
}
