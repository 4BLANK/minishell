/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:40:44 by amasdouq          #+#    #+#             */
/*   Updated: 2023/11/25 20:00:15 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base_int(long n, long base)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count += ft_putchar('-');
	}
	if (n < base)
	{
		count += ft_putchar("0123456789abcdef"[n % base]);
		return (count);
	}
	if (n >= base)
	{
		count += ft_putnbr_base(n / base, base);
		count += ft_putchar("0123456789abcdef"[n % base]);
	}
	return (count);
}
