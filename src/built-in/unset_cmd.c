#include "../../includes/minishell.h"

static int remove_envnode(t_envlist **env, size_t pos);
static int dalete_var(t_envlist *env, char *name);

int unset_cmd(char **args)
{
    size_t i;

    i = 1;
    if (args == NULL)
        return (EXIT_FAILURE);
    if (str_arraysize(args) == 1)
        return(EXIT_SUCCESS);
    while (args[i])
    {
        if (env_exist(args[i]))
            dalete_var(sh->envlst, args[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}

static int remove_envnode(t_envlist **env, size_t pos)
{
    size_t i;
    t_envlist *tmp;
    t_envlist *node;

    i = 0;
    if (*env == NULL)
        return (EXIT_SUCCESS);
    tmp = *env;
    if (pos == 0)
    {
        *env = tmp->next;
        free(tmp->name);
        free(tmp);
        tmp = NULL;
        return (EXIT_SUCCESS);
    }
    else
    {
        while (tmp != NULL && i < pos - 1)
        {
            tmp = tmp->next;
            i++;
        }
        if (tmp == NULL || tmp->next == NULL)
            return (EXIT_SUCCESS);
        node = tmp->next->next;
        free((tmp->next)->name);
        free(tmp->next);
        tmp->next = node;
        tmp = NULL;
    }
    return (EXIT_SUCCESS);
}

static int dalete_var(t_envlist *env, char *name)
{
    size_t pos;
    t_envlist *lst;

    pos = 0;
    lst = env;
    while (lst != NULL)
    {
        if (ft_strncmp(name, lst->name, sizeof(name)) == 0)
        {
            remove_envnode(&sh->envlst, pos);
            break;
        }
        pos++;
        lst = lst->next;
    }
    return (EXIT_SUCCESS);
}

