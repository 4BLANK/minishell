#include "../../includes/minishell.h"

static int is_dir(char *pwd)
{
    DIR *dir;

    dir = NULL;
    if (access (pwd, F_OK) != -1) {
        if ((dir = opendir(pwd)) != NULL) {
            closedir (dir);
        } else {
            ft_error("cd", pwd, "Not a directory\n");
            return (-2);
        }
    } else {
        ft_error("cd", pwd, "No such file or directory\n");
        return (-1);
    }
    return (1);
}

int cd_cmd(char **args)
{
    char *pwd;
    char *home;

    home = NULL;
    pwd = NULL;
    if (str_arraysize(args) > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (EXIT_FAILURE);
    }
    pwd = args[1];
    if (pwd == NULL)
    {
        if (!(home = ft_getenv("HOME")))
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (EXIT_FAILURE);
        }
        pwd = home;
    }
    if (is_dir(pwd) != 1 || chdir(pwd))
        return (EXIT_FAILURE);
    // if (overwrite_env("PWD", pwd))
    //     return (free(home), EXIT_FAILURE);
    free(home);
    return (EXIT_SUCCESS);
}
