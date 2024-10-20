/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:17:52 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/12 03:09:01 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_nl_flag(char *str)
{
	int	i;

	i = 0;
	if ((!str[i]) || (str[i] && str[i] != '-'))
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] && str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo(char **args)
{
	int	nlflag;
	int	i;

	nlflag = 1;
	i = 1;
	if (!(args[i]))
	{
		ft_printf("\n");
		return (EXIT_SUCCESS);
	}
	while (args[i] && !check_nl_flag(args[i]))
	{
		nlflag = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf(args[i]);
		i++;
		if (args[i])
			ft_printf(" ");
	}
	if (nlflag)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
