#include "../../../includes/minishell.h"

int	append_redirect_output(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
    ft_putstr_fd("chnghl omnghl: ", 2);
    ft_putstr_fd(filename, 2);
		perror(" ");
		return (EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
	return (EXIT_SUCCESS);
}
