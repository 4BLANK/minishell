/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:34:39 by amasdouq          #+#    #+#             */
/*   Updated: 2023/12/04 04:30:37 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		count += write(1, "(null)", 6);
		return (count);
	}
	while (*s)
	{
		count += ft_putchar(*s);
		s++;
	}
	return (count);
}
