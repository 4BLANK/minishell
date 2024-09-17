#ifndef MINISHELL_H
#define MINISHELL_H 

#include "parser.h"
#include "executor.h"
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

typedef struct s_shell
{
  int ex_status;
  char *home;
  t_envlist *envlst;
  int pipefd[2];
} t_shell;

char **lst_tostrarray(t_argument *head);
int kickoff(t_ast_node *node);

extern t_shell *sh;

t_shell *setshell(char **env);
void handler(int sig);
int redirect(t_ast_node *cmd, int *left, int *right);
int parser (t_ast_node **ast, char *line);
int execute_pipeline(t_ast_node *node);
int execute_command(t_ast_node *node, int left, int right, int pipefd[2]);
int execute_or(t_ast_node *node);
int execute_and(t_ast_node *node);
int execute_group(t_ast_node *node, int left, int right);

#endif
