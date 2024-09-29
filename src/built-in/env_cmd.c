#include "../../includes/minishell.h"

int env_cmd(void)
{
    t_envlist *lst;

    lst = sh->envlst;
    if (lst == NULL)
        return (EXIT_SUCCESS);
    while (lst != NULL)
    {
        if (lst->value != NULL)
            ft_printf("%s=%s\n", lst->name, lst->value);
        lst = lst->next;
    }
    return (EXIT_SUCCESS);
}
