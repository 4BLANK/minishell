#include "../../../includes/minishell.h"

void	free_strarray(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

char	*get_cmd_path(char *env_path, char *cmd)
{
	char	*cmd_path;
	char	**splited_path;
	size_t	itr;

	itr = 0;
	cmd_path = NULL;
	splited_path = ft_split(env_path, ':');
	while (splited_path[itr] != NULL)
	{
		cmd_path = ft_strjoin(splited_path[itr], cmd);
		if (!access(cmd_path, F_OK) && !is_dir0(cmd_path))
		{
			free_strarray(splited_path);
			return (cmd_path);
		}
		free(cmd_path);
		itr++;
	}
	free_strarray(splited_path);
	return (NULL);
}

static int	linessssss(char *cmd_p, char **cmd_path, char *env_path, char *cmd)
{
	cmd_p = ft_strjoin("/", cmd);
	*cmd_path = get_cmd_path(env_path, cmd_p);
	if (cmd_path == NULL)
	{
		free(cmd_p);
		*cmd_path = ft_strdup(cmd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	get_commandpath(char **cmd_path, char *cmd)
{
	char	*env_path;
	char	*cmd_p;

	cmd_p = NULL;
	env_path = NULL;
	if (has_slash(cmd))
	{
		*cmd_path = ft_strdup(cmd);
		return (EXIT_SUCCESS);
	}
	env_path = ft_getenv("PATH");
	if (!cmd || !cmd[0])
		return (EXIT_SUCCESS);
	if (env_path == NULL)
	{
		*cmd_path = ft_strdup(cmd);
		return (EXIT_SUCCESS);
	}
	if (!linessssss(cmd_p, cmd_path, env_path, cmd))
		return (EXIT_SUCCESS);
	free(cmd_p);
	return (EXIT_SUCCESS);
}
