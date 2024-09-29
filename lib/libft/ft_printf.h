/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasdouq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 02:22:35 by amasdouq          #+#    #+#             */
/*   Updated: 2023/11/25 20:08:55 by amasdouq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_putnbr_base(size_t nbr, size_t base);
int	ft_putnbr_base_cap(size_t n, size_t base);
int	ft_putnbr_base_int(long n, long base);
int	ft_putstr(char *s);
int	ft_pre_putaddress(void *p);
int	ft_putaddress(void *p);

#endif
