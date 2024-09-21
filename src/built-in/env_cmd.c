#include "../../includes/minishell.h"

int env_cmd(void)
{
    size_t i;
    t_envlist *lst;

    i = 0;
    lst = sh->envlst;
    if (lst == NULL)
        return (EXIT_SUCCESS);
    while (lst != NULL)
    {
        if (lst->value != NULL)
            printf("%s=%s\n", lst->name, lst->value);
        lst = lst->next;
    }
    return (EXIT_SUCCESS);
}