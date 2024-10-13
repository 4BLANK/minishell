/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:02:20 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 03:02:53 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("chnghl omnghl: ", 2);
		ft_putstr_fd(filename, 2);
		perror(" ");
		return (EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
	return (EXIT_SUCCESS);
}
