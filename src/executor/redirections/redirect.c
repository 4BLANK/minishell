/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:02:19 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/20 12:24:31 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	red(t_file *tmp, int *status, int *left, int *right)
{
	if (tmp->type == AMBIGUOUS)
	{
		ft_putstr_fd("chnghl o mnghl: ", 2);
		ft_putstr_fd(tmp->name, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		*status = 1;
	}
	if (tmp->type == O_REDIRECTION)
	{
		*right = 0;
		*status = redirect_output(tmp->name);
	}
	if (tmp->type == I_REDIRECTION || tmp->type == HEREDOC)
	{
		*left = 0;
		*status = redirect_input(tmp->name);
	}
	if (tmp->type == APPEND)
	{
		*right = 0;
		*status = append_redirect_output(tmp->name);
	}
	if (*status)
		g_sh->ex_status = *status;
}

int	redirect(t_ast_node *cmd, int *left, int *right)
{
	t_file	*tmp;
	int		status;

	if (!(cmd->u_data.s_childs.right))
		return (EXIT_SUCCESS);
	tmp = cmd->u_data.s_childs.right->u_data.files;
	status = EXIT_SUCCESS;
	while (tmp)
	{
		red(tmp, &status, left, right);
		if (status)
			return (status);
		tmp = tmp->next;
	}
	return (0);
}
