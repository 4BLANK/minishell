/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:02:35 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 03:02:40 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		sh->ex_status = SIGINT + 128;
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	here_doc_handler(int sig)
{
	(void)sig;
	unlink(shd()->filename);
	free(shd()->filename);
	shd()->filename = NULL;
	tokens_lstclear(shd()->tokens);
	close(shd()->fd);
	distroy_envlst(&sh->envlst);
	free(sh);
	exit(DOOMSDAY);
}

void	handle_signals(int mode)
{
	if (mode == PARENT)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == HDOC)
	{
		signal(SIGINT, here_doc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (mode == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
