#include "../../includes/minishell.h"

int	pwd_cmd(char	**args)
{
	int     status;
	char    *pwd;
       
	pwd = NULL;
	status = 0;
	if (str_arraysize(args) > 1)
	{
		print_error("pwd: too many arguments\n", 2);
		return (1);
	}
    pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("%s\n", ft_getenv("PWD"));
		print_error("getcwd(): error!\n", 2);
		return (1);
	}
	ft_printf("%s\n", pwd);
	return (status);
}
