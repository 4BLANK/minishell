/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 04:58:52 by amasdouq          #+#    #+#             */
/*   Updated: 2023/11/24 08:35:54 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putaddress(void *p)
{
	int					count;
	unsigned long long	n;

	count = 0;
	n = (unsigned long long)p;
	if (n < 16)
	{
		count += ft_putchar("0123456789abcdef"[n % 16]);
		return (count);
	}
	if (n >= 16)
	{
		count += ft_putaddress((void *)(n / 16));
		count += ft_putchar("0123456789abcdef"[n % 16]);
	}
	return (count);
}

int	ft_pre_putaddress(void *p)
{
	int	count;

	count = 0;
	if (!p)
	{
		ft_putstr("(nil)");
		return (5);
	}
	count += ft_putstr("0x");
	count += ft_putaddress(p);
	return (count);
}
