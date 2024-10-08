/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:13:38 by mzelouan          #+#    #+#             */
/*   Updated: 2024/10/06 13:13:39 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_cmd(void)
{
	t_envlist	*lst;

	lst = sh->envlst;
	if (lst == NULL)
		return (EXIT_SUCCESS);
	while (lst != NULL)
	{
		if (lst->value != NULL)
			ft_printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
