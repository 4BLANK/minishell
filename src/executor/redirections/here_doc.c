#include "../../../includes/minishell.h"

char	*create_file_name(void)
{
	static int	num = 0;
	char		*str;
	char		*res;
	char		*num_value;

	res = NULL;
	num_value = ft_itoa(num);
	str = "/tmp/heredoc_tmp";
	res = ft_strjoin(str, num_value);
	free(num_value);
	num++;
	return (res);
}

static int	child_routine(char **delimiter, int fd, int flag)
{
	char	*line;

	line = NULL;
	handle_signals(HDOC);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putstr_fd("chnghl o mnghl: warning: here-document delimited by EOF,\
				wanted: ", 2);
			ft_putstr_fd(*delimiter, 2);
			ft_putstr_fd("\n", 2);
      close(fd);
			return (EXIT_SUCCESS);
		}
		if (!ft_strcmp(*delimiter, line))
		{
			if (flag == 1)
				line = expand_heredoc(line);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
      free(line);
		}
		else
			return (EXIT_SUCCESS);
	}
}

int	here_doc(char **delimiter, int flag, t_token **toklst)
{
	int		fd;
	char	*file_name;
	pid_t	pid;
	int		status;

	file_name = create_file_name();
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	status = 0;
	if (fd < 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
		{
			status = WTERMSIG(status) + 128;
			ft_printf("\n");
		}
		if (!status)
		{
			free(*delimiter);
			*delimiter = file_name;
		}
    else if (status == DOOMSDAY)
      free(file_name);
    close(fd);
	}
	else if (pid == 0)
	{
    set_heredoc_signal_data(toklst, file_name, *delimiter, fd);
		status = child_routine(delimiter, fd, flag);
		free(file_name);
		free(*delimiter);
		*delimiter = NULL;
		tokens_lstclear(toklst);
		distroy_envlst(&sh->envlst);
		free(sh);
    close(fd);
		exit(status);
	}
	return (status);
}
