/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:03:09 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 23:40:13 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PARENT 0
#define CHILD 1
#define IGNORE 2
#define HDOC 3
#define SAVE 0
#define RECOVER 1

void	handle_signals(int mode);
int		get_commandpath(char **cmd_path, char *cmd);
int		redirect_input(char *filename);
int		redirect_output(char *filename);
int		append_redirect_output(char *filename);
int		check_error_type(char *cmd_path);
int		specify_error(int status, char *cmd_path);
int		tiny_check(void);
int		echo(char **args);
int		pre_exec_errors(char *cmd, char *cmd_path);
int		is_built_in(char *str);
int		has_slash(char *str);
int		is_dir0(char *pwd);
