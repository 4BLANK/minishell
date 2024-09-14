#include "../../includes/minishell.h"

void free_strarray(char **str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

bool env_exist(char *name, char **env)
{
    size_t i;

    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], name, ft_strlen(name)))
            return (true);
        i++;
    }
    return (false);
}

char *getenv_name1(char *str)
{
    char *tmp;
    int i;

    i = 1;
    while (str[i] && !is_space(str[i]) && str[i] != '=')
        i++;
    tmp = (char *)ft_calloc(i + 1, sizeof(char));
    if (tmp == NULL)
        return NULL;
    i = 0;
    while (str[i] && !is_space(str[i]) && str[i] != '=')
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char **set_newenv(char *arg, char **env, int unset)
{
    char **envlst;
    size_t i;
    size_t j;
    size_t size;
    char *tmp;

    i = 0;
    j = 0;
    tmp = NULL;
    size = str_arraysize(env);
    if (unset == 0)
        size += 2;
    envlst = (char **)ft_calloc(sizeof(char *), size);
    if (envlst == NULL)
        return (NULL);
    while (env[i])
    {
        if (!ft_strncmp(arg, env[i], ft_strlen(arg)))
        {
            if (unset == 0)
            {
                envlst[j] = ft_strdup(env[i]);
                j++;
            }
        }
        else 
        {
            envlst[j] = ft_strdup(env[i]);
            j++;
        }
        i++;
    }
    if (unset == 0 && !(envlst[j++] = ft_strdup(arg)))
        return (NULL);
    envlst[j] = NULL;
    return (envlst);
}

int overwrite_env(char *arg, char **env, char *name)
{
    size_t i;
    char *tmp;

    i = 0;
    tmp = NULL;
    while (env[i] != NULL)
    {
        if (!ft_strncmp(env[i], name, ft_strlen(name)))
        {
            tmp = env[i];
            env[i] = ft_strdup(arg);
            if (env[i] == NULL)
                return (free(tmp), EXIT_FAILURE);
            break;
        }
        i++;
    }
    return (free(tmp), EXIT_SUCCESS);
}

char **regenerate_env(char *arg, char **env)
{
    char **new_envlst;

    new_envlst = set_newenv(arg, env, 0);
    if (new_envlst == NULL)
        return (NULL);
    free_strarray(env);
    return (new_envlst);
}

int setenv_fromlocal(char *name, char ***env)
{
    char *newvalue;
    char *arg;
    char *tmp;

    newvalue = NULL;
    tmp = NULL;
    arg = NULL;
    newvalue = ft_getenv(name);
    if (newvalue == NULL)
        return EXIT_FAILURE;
    tmp = ft_strjoin(name, "=");
    if (tmp == NULL)
        return (free(newvalue), EXIT_FAILURE);
    arg = ft_strjoin(tmp, newvalue);
    if (arg == NULL)
    {
        free(tmp);
        return (free(newvalue), EXIT_FAILURE);
    }
    free(tmp);
    free(newvalue);
    if ((*env = regenerate_env(arg, *env)) == NULL)
            return (EXIT_FAILURE);
    return EXIT_SUCCESS;
}

int ft_setenv(char *arg, char ***env, int exportflag)
{
    char **new_envlst;
    char *name;
    char *newvalue;

    new_envlst = NULL;
    newvalue = NULL;
    if (!(name = getenv_name1(arg)))
        return (EXIT_SUCCESS);
    if (env_exist(name, *env) && env_exist(name, *env))
    {
        //printf("%s exist in both\n", name);
        /*
         * the variable that we want to export exist 
         * in both the original env and the local one
         * we change its value in both envs
        */
        if (overwrite_env(arg, *env, name))
            return (EXIT_FAILURE);
        if (overwrite_env(arg, *env, name))
            return (EXIT_FAILURE);
        //printf("1\n");
        //print_lst(*env);
    }
    else if (env_exist(name, *env))
    {
        /*
         * the variable already exist in the local env 
         * but not in the original one
         * the varibale sould be added to the original env 
         * with the same value as the local one only if the
         * value is not specified (export DATA if the equale
            * signe does not exit
        */
        // if (value == NULL)
        if (!ft_strchr(arg, '='))
        {
            if(setenv_fromlocal(name, env))
            {
                //printf("1\n");
                return (free(name), EXIT_FAILURE);
            }
        }
        else 
        {
            if (overwrite_env(arg, *env, name))
                return (EXIT_FAILURE);
            if (exportflag == 1)
            {
                if ((new_envlst = regenerate_env(arg, *env)) == NULL)
                    return (EXIT_FAILURE);
                *env = new_envlst;
            }
        }
    }
    else 
    {
        /*
         * if the variable does note exist in both
         * envs we add the variable is env and envlocal
         * only is export command was specified
        */
        if (exportflag == 1)
        {
            if ((new_envlst = regenerate_env(arg, *env)) == NULL)
                return (EXIT_FAILURE);
            *env = new_envlst;
        }
        if ((new_envlst = regenerate_env(arg, *env)) == NULL)
            return (EXIT_FAILURE);
        *env = new_envlst;
    }
    return(EXIT_SUCCESS);
}

int export_cmd(char **args, char ***env, int exportflag)
{
    size_t i;

    i = exportflag;
    if (args == NULL)
        return EXIT_FAILURE;
    if (str_arraysize(args) == 1 && exportflag)
        return(env_cmd(*env, 1));
    while (args[i])
    {
        if (ft_setenv(args[i], env, exportflag))
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}