/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:01:56 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 23:41:29 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	too_manylines(int *status)
{
	if (g_sh && g_sh->args)
	{
		free_strarray(g_sh->args);
		g_sh->args = NULL;
	}
	if (g_sh && g_sh->ast)
	{
		ast_distroy(&(g_sh->ast), 1);
		g_sh->ast = NULL;
	}
	if (g_sh && g_sh->envlst)
	{
		distroy_envlst(&(g_sh->envlst));
		g_sh->envlst = NULL;
	}
	if (g_sh)
	{
		*status = g_sh->ex_status;
		free(g_sh);
		g_sh = NULL;
	}
}

int	free_mem(int flag)
{
	int	status;

	status = 0;
	if (flag == 1)
		too_manylines(&status);
	else
	{
		if (g_sh && g_sh->args)
		{
			free_strarray(g_sh->args);
			g_sh->args = NULL;
		}
		if (g_sh && g_sh->ast)
		{
			ast_distroy(&(g_sh->ast), 1);
			g_sh->ast = NULL;
		}
	}
	return (status);
}
