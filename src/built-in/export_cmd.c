#include "../../includes/minishell.h"

//TODO: kemal had l9wada expandi ta wild cards
char *export_expander(char *str)
{
    size_t i;
    char *newstr;
    char *envname;
    int flag;
    char *tmp;

    i = 0;
    flag = 0;
    newstr = NULL;
    tmp = NULL;
    envname = NULL;
    while (str[i])
    {
        if (flag == 0 && str[i] == QUOTE)
            flag = 1;
        else if (flag == 1 && str[i] == QUOTE)
            flag = 0;
        if (flag == 0 && str[i] == DOLLAR_SIGN && str[i + 1]) 
        {
            tmp = expand_pid_or_exit(newstr, str[i], str[i + 1]);
            if (tmp != NULL)
            {
                newstr = tmp;
                i++;
            }
            else 
            {
                envname = get_name(str, i + 1);
                tmp = ft_strdup(ft_getenv(envname));
                newstr = concat(newstr, tmp, 0);
                i = i + ft_strlen(envname);
                free(tmp);
                free(envname);
            }
        }
        else
            newstr = concat(newstr, str + i, 1);
        i++;
    }
    return (newstr);
}

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
        if (ft_strcmp(env->name, name))
        {
            tmp = env->value;
            env->value = value;
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
    char *new_arg;
    char *name;
    char *value;

    name = NULL;
    value = NULL;
    new_arg = export_expander(arg);
    if (invalid_arg(new_arg))
        return (EXIT_FAILURE);
    name = getenv_name(new_arg);
    value = getenv_value(new_arg);
    ft_setenv(name, value);
    free(new_arg);
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
