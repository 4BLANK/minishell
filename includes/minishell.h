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

typedef struct s_tmps
{
    char *filename;
    struct s_tmps *next;
} t_tmps;

typedef struct s_shell
{
  int ex_status;
  char *home;
  t_envlist *envlst;
  t_ast_gc *trash;
  int pipefd[2];
  char **args;
  t_tmps *tmps;
} t_shell;

typedef struct s_pair
{
  int left;
  int right;
} t_pair;

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
int execute_group(t_ast_node *node, int left, int right, int clonefds[2]);
int built_ins(char **args, int *status, t_pair *pipe_location, int pipefd[2]);
int execute(char **args, t_pair *pipe_location, int pipefd[2], int *status);
void distroy_tmps(t_tmps **lst);

#endif
