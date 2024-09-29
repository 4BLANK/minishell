/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 02:23:57 by amasdouq          #+#    #+#             */
/*   Updated: 2023/12/04 04:54:30 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(const char format, va_list ap)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (format == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (format == 'd' || format == 'i')
		count += ft_putnbr_base_int(va_arg(ap, int), 10);
	else if (format == 'x')
		count += ft_putnbr_base(va_arg(ap, unsigned int), 16);
	else if (format == 'X')
		count += ft_putnbr_base_cap(va_arg(ap, unsigned int), 16);
	else if (format == 'u')
		count += ft_putnbr_base(va_arg(ap, unsigned int), 10);
	else if (format == 'p')
		count += ft_pre_putaddress(va_arg(ap, void *));
	else
		count += ft_putchar(format);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!(*format))
				return (-1);
			count += print_format(*format, ap);
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (count);
}
