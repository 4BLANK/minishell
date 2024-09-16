#include "../../includes/minishell.h"

static void set_variables(char **old, char **new, char *pwd, char **env)
{
    char *tmp;

    tmp = NULL;
    *old = NULL;
    *new = NULL;
    (void)env;
    tmp = ft_getenv("PWD");
    *old = ft_strjoin("OLDPWD=", tmp);
    free(tmp);
    tmp = NULL;
    if (*old == NULL)
        return ;
    *new = ft_strjoin("PWD=", pwd);
    if (*new == NULL)
    {
        free(old);
        return ;
    }
}

static int is_dir(char *pwd)
{
    DIR *dir;

    dir = NULL;
    if (access (pwd, F_OK) != -1) {
        if ((dir = opendir(pwd)) != NULL) {
            closedir (dir);
        } else {
            printf("cd: %s: Not a directory\n", pwd);
            return (-2);
        }
    } else {
        printf("cd: %s: No such file or directory\n", pwd);
        return (-1);
    }
    return (1);
}

int cd_cmd(char **args, char **env)
{
    char *pwd;
    char *home;
    char *old_pwd;
    char *new_pwd;

    home = NULL;
    pwd = NULL;
    if (str_arraysize(args) > 2)
    {
        print_error("cd: too many arguments\n", 2);
        return (EXIT_FAILURE);
    }
    pwd = args[1];
    if (pwd == NULL)
    {
        if (!(home = ft_getenv("HOME")))
        {
            print_error("cd: HOME not set\n", 2);
            return (EXIT_FAILURE);
        }
        pwd = home;
    }
    if (is_dir(pwd) != 1 || !chdir(pwd))
        return (EXIT_FAILURE);
    set_variables(&old_pwd, &new_pwd, pwd, env);
    if (overwrite_env(old_pwd, env, "OLDPWD") 
        || overwrite_env(new_pwd, env, "PWD"))
        return (free(home), EXIT_FAILURE);
    free(home);
    return (EXIT_SUCCESS);
}
