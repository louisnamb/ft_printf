/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:43:45 by lnambaji          #+#    #+#             */
/*   Updated: 2023/03/29 16:09:55 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
//#include "libft.h"
#include "ft_printf.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || !fd)
		return ;
	while (*s)
		write(fd, &*s++, 1);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

static int	digitspecifier(const char c, va_list curr_varr)
{
	int	num;

	num = va_arg(curr_varr, int);
	ft_putnbr_fd(num, 1);
	return (1);
}

static int	validspecifier(const char c)
{
	return (c == 'd' || c == 's' || c == 'p' || c == 'd' || c == 'i' 
	|| c == 'u' || c == 'x' || c == 'u' || c == 'x' || c == 'X');
}

void	whichspecifier(const char c, va_list curr_varr)
{
	if (c =='d')
		digitspecifier(c, curr_varr);
	else
		return ;
	/*else if (c =='s')
	else if (c =='p')
	else if (c =='d')
	else if (c =='i')		
	else if (c =='u') 
	else if (c =='x') 
	else if (c =='u') 
	else if (c =='x') 
	else (c =='X')*/
}

int	ft_printf(const char *format, ...)
{
	va_list	input;
	
	va_start(input, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (validspecifier(*(format + 1)))
				whichspecifier(*(format + 1), input);
			else
				break;
		}
		++format;
	}
	va_end(input);
	return (0);
}

int	main(void)
{
	ft_printf("%dhellof%df%d", 6, 6, 0);
	return 0;
}

/*
Printf KNOWLEDGE:
	- The format parameter is in charge of the string part of the 
	input. i.e., its in charge of the flags and specifiers of the 
	input.
Printf FYI:
	- Have a checker counts the number of times "%" appears in 
	the first arguments string, this will give you an estimate 
	as to the number of variables inputted
	- How are you going to know the type when youre doing "va_arg(va_list param, variable type)"?
	I say use the "typeof()" function

*/