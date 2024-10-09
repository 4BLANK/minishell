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

static void	printerr(char *str, int flag)
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

static void	on_slash(char *cmd)
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
		}
	}
	else
	{
		printerr(cmd, 3);
		sh->ex_status = 127;
	}
}

int	pre_exec_errors(char *cmd, char *cmd_path)
{
	sh->ex_status = 0;
	if (has_slash(cmd))
		on_slash(cmd);
	else
	{
		if (!cmd_path || access(cmd_path, X_OK))
		{
			printerr(cmd, 4);
			sh->ex_status = 127;
		}
	}
	return (sh->ex_status);
}
