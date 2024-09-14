#ifndef MINISHELL_H
#define MINISHELL_H 

#include <readline/readline.h>
#include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <dirent.h>

#include "parser.h"
#include "executor.h"

typedef struct s_shell
{
    // shell data
    int ex_status;
    char *home;
    t_envlist *envlst;
} t_shell;

extern t_shell *sh;

t_shell *setshell(char **env);
int parser (t_ast_node **ast, char *line);
#endif
