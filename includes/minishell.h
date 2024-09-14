#ifndef MINISHELL_H
#define MINISHELL_H 

#include "parser.h"
#include "executor.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

typedef struct s_shell
{
    // shell data
    int ex_status;
    char *home;
    t_envlist *envlst;
} t_shell;

char **lst_tostrarray(t_argument *head);
int kickoff(t_ast_node *node);

extern t_shell *sh;

t_shell *setshell(char **env);
int redirect(t_ast_node *cmd, int *left, int *right);
int parser (t_ast_node **ast, char *line);

#endif
