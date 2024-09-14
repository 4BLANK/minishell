#include "../../includes/minishell.h"

int env_cmd(char **env, int exp_flag)
{
    size_t i;

    i = 0;
    if (str_arraysize(env) == 0)
        return (EXIT_SUCCESS);
    while (env[i])
    {
        if (exp_flag == 1)
            printf("%s\n", env[i]);
        else 
        {
            if (ft_strchr(env[i], '='))
                printf("%s\n", env[i]);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}