/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:02:16 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 03:02:53 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cr_lines(char *line, int fd, int flag)
{
	if (flag == 1)
		line = expand_heredoc(line);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
}

int	child_routine(char **delimiter, int fd, int flag)
{
	char	*line;

	line = NULL;
	handle_signals(HDOC);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putstr_fd("chnghl o mnghl: warning: here-document delimited by EOF,\
				wanted: ", 2);
			ft_putstr_fd(*delimiter, 2);
			ft_putstr_fd("\n", 2);
			close(fd);
			return (EXIT_SUCCESS);
		}
		if (!ft_strcmp(*delimiter, line))
			cr_lines(line, fd, flag);
		else
			return (EXIT_SUCCESS);
	}
}
