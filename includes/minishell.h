/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 06:00:15 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/13 23:40:22 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "executor.h"
# include "parser.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_tmps
{
	char			*filename;
	struct s_tmps	*next;
}					t_tmps;

typedef struct s_shell
{
	unsigned char	ex_status;
	t_envlist		*envlst;
	int				pipefd[2];
	char			**args;
	t_ast_node		*ast;
}					t_shell;

typedef struct s_pair
{
	int				left;
	int				right;
}					t_pair;

typedef struct s_hdata
{
	t_token			**tokens;
	char			*delimiter;
	char			*filename;
	int				fd;
}					t_hdata;

char				**lst_tostrarray(t_argument *head);
int					kickoff(t_ast_node *node);

extern t_shell		*g_sh;

t_shell				*setshell(char **env);
void				handler(int sig);
int					redirect(t_ast_node *cmd, int *left, int *right);
int					parser(t_ast_node **ast, char *line);
int					execute_pipeline(t_ast_node *node);
int					execute_command(t_ast_node *node, t_pair *pl, int pipefd[3],
						pid_t *last_pid);
int					execute_or(t_ast_node *node);
int					execute_and(t_ast_node *node);
int					execute_group(t_ast_node *node, t_pair *pl, int clonefds[3],
						pid_t *last_pid);
int					built_ins(t_ast_node *node, t_pair *pipe_location,
						int pipefd[3]);

void				ft_setenv(char *name, char *value);
int					overwrite_env(char *name, char *value);
int					exit_cmd(char **args, t_ast_node **ast);
int					free_mem(int s);
void				set_heredoc_signal_data(t_token **t, char *f, char *d,
						int fd);
t_hdata				*shd(void);
char				**env_tostrarray(void);
void				close_save(int save[2]);
int					redirect_fail(int pipefd[3], int save[2]);
int					redirect_fail2(char *cmd_path, int pipefd[3], char **e);
int					line_rm(char *cmd);
void				printerr(char *str, int flag);
int					child_rt(char **delimiter, int fd, int flag);
int					here_doc(char **delimiter, int flag, t_token **toklst);
#endif
