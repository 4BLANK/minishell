/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:02:14 by amasdouq          #+#    #+#             */
/*   Updated: 2024/10/13 03:02:53 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_heredoc_signal_data(t_token **t, char *f, char *d, int fd)
{
	shd()->tokens = t;
	shd()->filename = f;
	shd()->delimiter = d;
	shd()->fd = fd;
}

t_hdata	*shd(void)
{
	static t_hdata	hdata;

	return (&hdata);
}
