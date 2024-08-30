#ifndef MINISHELL_H
#define MINISHELL_H 

#include <readline/readline.h>
#include <readline/history.h>

#include "parser.h"
#include "executor.h"

typedef struct s_shell
{
    // shell data
    int l_exitstatus;
    char **env;
} t_shell;

int parser (t_ast_node **ast, char *line, char **env);

#endif
