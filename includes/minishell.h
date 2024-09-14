#ifndef MINISHELL_H
#define MINISHELL_H 

#include "parser.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>


typedef struct s_shell
{
    // shell data
    int l_exitstatus;
    char **env;
} t_shell;

int parser (t_ast_node **ast, char *line, char **env);
int execute_cmd(t_ast_node *cmd, char **env);
char **lst_tostrarray(t_argument *head);
int kickoff(t_ast_node *node);
#endif
