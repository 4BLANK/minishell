#include "../../includes/minishell.h"

int unset_cmd(char **args, char ***env)
{

    (void)args;
    (void)env;
    // size_t i;
    // char **envnew;

    // i = 1;
    // if (args == NULL)
    //     return EXIT_FAILURE;
    // if (str_arraysize(args) == 1)
    //     return(EXIT_SUCCESS);
    // while (args[i])
    // {
    //     if (env_exist(args[i], *env))
    //     {
    //         if (!(envnew = set_newenv(args[i], *env, 1)))
    //             return (EXIT_FAILURE);
    //         free_strarray(*env);
    //         *env = envnew;
    //     }
    //     if (env_exist(args[i], *env))
    //     {
    //         if (!(envnew = set_newenv(args[i], sh->envlst, 1)))
    //             return (EXIT_FAILURE);
    //         free_strarray(sh->envlst);
    //         *env = envnew;
    //     }
    //     envnew = NULL;
    //     i++;
    // }
    // return (EXIT_SUCCESS);
    return(0);
}