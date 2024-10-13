/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:09:34 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 03:12:16 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 0)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

static void	reduce_line(char **args, char *tmp)
{
	if (!args[1][0])
	{
		ft_putstr_fd("chnghl o mnghl: exit:", 2);
		ft_putstr_fd(" numeric agrument required\n", 2);
		free_mem(1);
		free(tmp);
		exit(2);
	}
	tmp = ft_strtrim(args[1], " \t\n\f\v\r");
	if (is_numeric(tmp))
		sh->ex_status = ft_atoi(tmp);
	else
	{
		ft_putstr_fd("chnghl o mnghl: exit:", 2);
		ft_putstr_fd(" numeric agrument required\n", 2);
		free_mem(1);
		free(tmp);
		exit(2);
	}
}

int	exit_cmd(char **args, t_ast_node **ast)
{
	char	*tmp;

	(void)ast;
	tmp = NULL;
	ft_putstr_fd("exit\n", 1);
	if (!args)
		exit(free_mem(1));
	if (args[1])
		reduce_line(args, tmp);
	if (tmp && args[2])
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("chnghl o mnghl: exit:", 2);
		ft_putstr_fd(" too many arguments\n", 2);
		return (free(tmp), 2);
	}
	free(tmp);
	exit(free_mem(1));
}
