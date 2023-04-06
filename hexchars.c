/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexchars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:18:28 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/06 13:03:02 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_u_putnbr_fd(unsigned int n, int fd, int total, int *sum)
{
	if (n < 0)
	{
		total += ft_putchar_fd('-', fd);
		ft_u_putnbr_fd(-n, fd, total, sum);
	}
	else if (n >= 10)
	{
		total++;
		ft_u_putnbr_fd(n / 10, fd, total, sum);
		total += ft_putchar_fd(n % 10 + '0', fd);
	}
	else
	{
		*sum = total;
		total += ft_putchar_fd(n + '0', fd);
	}
	return (*sum + 1);
}

int	ft_hex_putstr(char *s, int fd, int length, int ptr)
{
	int	sum;

	sum = 0;
	if (!s)
		return (0);
	if (ptr)
		sum += write(fd, "0x", 2);
	while (length > 0)
	{
		sum += write(fd, &s[length], 1);
		length--;
	}
	write(fd, &s[length], 1);
	return (sum);
}

int	ft_hex_length(unsigned long num, int base)
{
	int	length;

	length = 0;
	while (num != 0)
	{
		num /= base;
		length++;
	}
	return (length);
}

int	ft_convert(unsigned long num, int base, int low, int ptr)
{
	char			*uphexi;
	char			*p_str;
	char			*final;
	int				chck;
	unsigned long	dummy;

	dummy = num;
	chck = 0;
	uphexi = "0123456789ABCDEF0123456789abcdef";
	if (low)
		chck = 16;
	p_str = malloc(sizeof(char) * ft_hex_length(num, base) + 1);
	if (!p_str)
		return (0);
	final = p_str;
	while (dummy != 0)
	{
		*p_str = uphexi[dummy % base + chck];
		dummy /= base;
		p_str++;
	}
	*p_str = '\0';
	return (ft_hex_putstr(final, 1, ft_hex_length(num, base), ptr));
}
