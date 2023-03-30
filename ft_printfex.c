/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:43:45 by lnambaji          #+#    #+#             */
/*   Updated: 2023/03/30 14:58:30 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
//#include "libft.h"
#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	sum;
	int	len;

	sum = 0;
	len = ft_strlen(s);
	if (!s || !fd)
		return (sum);
	while (*s)
		sum = write(fd, &*s++, len);
	return (sum);
}

int	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (0);
	write(fd, &c, 1);
	return (1);
}

int	ft_putnbr_fd(int n, int fd)
{
	int	sum;

	sum = 0;
	if (n == -2147483648)
		sum += ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		sum++;
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);	
	}
	else if (n >= 10)
	{
		sum++;
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
	{
		ft_putchar_fd(n + '0', fd);
		sum++;
	}
	return (sum);
}
/*
static int	digitspecifier(const char c, va_list curr_varr)
{
	int	num;
	num = va_arg(curr_varr, int);
	ft_putnbr_fd(num, 1);
	return (1);
}*/

static int	validspecifier(const char c)
{
	return (c == 'd' || c == 's' || c == 'p' || c == 'i' 
	|| c == 'u' || c == 'c' || c == 'x' || c == 'X');
}

int	whichspecifier(const char c, va_list curr_varr)
{
	int	sum;

	sum = 0;
	if (c == 'd')
		sum = ft_putnbr_fd((int)va_arg(curr_varr, int), 1);
	else if (c == 's')
		sum = ft_putstr_fd((char *)va_arg(curr_varr, char *), 1);
	else if (c == 'c')
		sum = ft_putchar_fd((char)va_arg(curr_varr, int), 1);
	/*else if (c == 'p')
	else if (c == 'i')
	else if (c == 'u')
	else if (c == 'x')
	else if (c == 'X')*/
	return (sum);

}

int	ft_printf(const char *format, ...)
{
	va_list	input;
	int	sum;

	sum = 0;
	va_start(input, format);
	while (*format)
	{
		if (*format == '%' && validspecifier(*(format + 1)))
		{
			sum += whichspecifier(*(format + 1), input);
			format++;
		}
		else
			sum += write(1, format, 1);
		++format;
		sum++;
	}
	va_end(input);
	
	return (sum);
}

int	main(void)
{
	char *str = "hello";
	int len1, len2;

	len1 = 0;
	len2 = 0;
	len1 = ft_printf("%d hello %s %d", 6, str, 0);
	printf("\n");
	len2 = printf("%d hello %s %d", 6, str, 0);
	printf("you: %d real: %d", len1, len2);
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
