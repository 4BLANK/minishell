#include "../../includes/minishell.h"

bool env_exist(char *name)
{
    t_envlist *lst;

    lst = sh->envlst;
    while (lst != NULL)
    {
        if (!ft_strncmp(lst->name, name, ft_strlen(name)))
            return (true);
        lst = lst->next;
    }
    return (false);
}

int ft_error(char *cmd, char *arg, char *error)
{
    ft_putstr_fd("changal: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(error, 2);
    return (EXIT_FAILURE);
}

int invalid_arg(char *arg)
{
    size_t i;

    i = 0;
    if(arg == NULL)
        return (EXIT_FAILURE);
    if (!ft_isalpha(arg[0]) && arg[0] != '_')
        return (ft_error("export", arg, "not a valid identifier\n"));
    while (arg[i] && arg[i] != '=')
    {   
        if (arg[i] != '_' && !ft_isalpha(arg[i]) 
            && !ft_isalnum(arg[i]))
            return (ft_error("export", arg, "not a valid identifier\n"));
        i++;
    }
    return (EXIT_SUCCESS);
}

int overwrite_env(char *name, char *value)
{
    t_envlist *env;
    char *tmp;

    tmp = NULL;
    env = sh->envlst;
    if (!name || !value)
        return (EXIT_FAILURE);
    while (env != NULL)
    {
        if (ft_strncmp(env->name, name, sizeof(name)) == 0)
        {
            tmp = env->value;
            env->value = value;
            break;
        }
        env = env->next;
    }
    free(tmp);
    free(name);
    return (EXIT_SUCCESS);
}

void ft_setenv(char *name, char *value)
{
    t_envlist *var;

    var = NULL;
    if (name == NULL)
        return ;
    value = remove_quote(value);
    if (env_exist(name) && value != NULL)
    {
        if (overwrite_env(name, value))
            return ;
    }
    else if (env_exist(name) && value == NULL)
        return ;
    else
    {
        var = lstnew_env(name, value);
        if (var == NULL)
            return ;
        lstadd_env_back(&sh->envlst, var);
    }
}

int export_var(char *arg)
{
    char *name;
    char *value;

    name = NULL;
    value = NULL;
    if (invalid_arg(arg))
        return (EXIT_FAILURE);
    name = getenv_name(arg);
    value = getenv_value(arg);
    ft_setenv(name, value);
    return (EXIT_SUCCESS);
}

int export_cmd(char **args)
{
    size_t i;
    int status;
    
    i = 1;
    status = 0;
    if (str_arraysize(args) == 1)
        print_env(sh->envlst);
    while (args[i] != NULL)
    {
        status = export_var(args[i]);
        i++;
    }
    return (status);
}
