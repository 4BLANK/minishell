/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:14:00 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/10 17:33:27 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_cmd(char **args)
{
	int		status;
	char	*pwd;

	pwd = NULL;
	status = 0;
	if (str_arraysize(args) > 1)
	{
		print_error("pwd: too many arguments\n", 2);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_error("getcwd(): error!\n", 2);
		return (1);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (status);
}
