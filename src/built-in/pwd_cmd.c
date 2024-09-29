#include "../../includes/minishell.h"

int pwd_cmd(char **args)
{
    int status;
    char *pwd;

    pwd = NULL;
    status = 0;
    if (str_arraysize(args) > 1)
    {
        print_error("pwd: too many arguments\n", 2);
        status = 1;
        return status;
    }
    if (!(pwd = getcwd(NULL, 0)))
    {
        status = 1;
        print_error("getcwd(): error!\n", 2);
        return status;
    }
    ft_printf("%s\n", pwd);
    return status;
}
