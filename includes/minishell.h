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
  unsigned char ex_status;
  t_envlist *envlst;
  int pipefd[2];
  char **args;
  t_ast_node *ast;
} t_shell;

typedef struct s_pair
{
  int left;
  int right;
} t_pair;

typedef struct s_hdata
{
  t_token **tokens;
  char *delimiter;
  char *filename;
  int fd;
} t_hdata;

char **lst_tostrarray(t_argument *head);
int kickoff(t_ast_node *node);

extern t_shell *sh;

t_shell *setshell(char **env);
void handler(int sig);
int redirect(t_ast_node *cmd, int *left, int *right);
int parser (t_ast_node **ast, char *line);
int execute_pipeline(t_ast_node *node);
int execute_command(t_ast_node *node, t_pair *pl, int pipefd[3], pid_t *last_pid);
int execute_or(t_ast_node *node);
int execute_and(t_ast_node *node);
int execute_group(t_ast_node *node, t_pair *pl, int clonefds[3], pid_t *last_pid);
int built_ins(t_ast_node *node, t_pair *pipe_location, int pipefd[3]);

void	ft_setenv(char *name, char *value);
int	overwrite_env(char *name, char *value);
int exit_cmd(char **args, t_ast_node **ast);
int free_mem(int s);
void set_heredoc_signal_data(t_token **t, char *f, char *d, int fd);
t_hdata *shd();
char	**env_tostrarray();
void	close_save(int save[2]);
int	redirect_fail(int pipefd[3], int save[2]);
int	redirect_fail2(char *cmd_path, int pipefd[3], char **e);
int	line_rm(char *cmd);
void	printerr(char *str, int flag);
void	cr_lines(char *line, int fd, int flag);
int	child_routine(char **delimiter, int fd, int flag);

#endif
