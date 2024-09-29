/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_cap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 04:04:47 by amasdouq          #+#    #+#             */
/*   Updated: 2023/11/25 20:08:27 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base_cap(size_t n, size_t base)
{
	int	count;

	count = 0;
	if (n < base)
	{
		count += ft_putchar("0123456789ABCDEF"[n % base]);
		return (count);
	}
	if (n >= base)
	{
		count += ft_putnbr_base_cap(n / base, base);
		count += ft_putchar("0123456789ABCDEF"[n % base]);
	}
	return (count);
}
