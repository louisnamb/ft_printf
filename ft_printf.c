/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:43:45 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/04 15:07:03 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
//#include "libft.h"
#include "ft_printf.h"

unsigned int    ft_u_putnbr_fd(unsigned int n, int fd, int total, int *sum)
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
	{
		sum += 6;
		write(fd, "0x7ffe", 6);
	}
	while (length > 0)
	{
		sum += write(fd, &s[length], 1);
		length--;
	}
	write(fd, &s[length], 1);
	return (sum);
}

int	ft_hex_length(int num, int base)
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

int	ft_convert(unsigned int num, int base, int low, int ptr)
{
	char			*uphexi;
	char			*p_str;
	char			*final;
	int				chck;
	unsigned int	dummy;

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
	int	len;

	len = ft_strlen(s);
	if (!s || !fd)
		return (0);
	return (write(fd, &*s, len));
}

int	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (0);
	return (write(fd, &c, 1));
}

int	ft_putnbr_fd(int n, int fd, int total, int *sum)
{
    if (n == -2147483648)
        total += ft_putstr_fd("-2147483648", fd);
    else if (n < 0)
    {
        total += ft_putchar_fd('-', fd);
        ft_putnbr_fd(-n, fd, total, sum);    
    }
    else if (n >= 10)
    {
        total++;
        ft_putnbr_fd(n / 10, fd, total, sum);
        total += ft_putchar_fd(n % 10 + '0', fd);
    }
    else
    {
        *sum = total;
        total += ft_putchar_fd(n + '0', fd);
    }
    return (*sum + 1);
}

int	whichspecifier(const char c, va_list curr_varr)
{
	int	sum;

	sum = 0;
	if (c == 'd' || c == 'i')
		sum = ft_putnbr_fd((int)va_arg(curr_varr, int), 1, sum, &sum);
	else if (c == 's')
		sum = ft_putstr_fd((char *)va_arg(curr_varr, char *), 1);
	else if (c == 'c')
		sum = ft_putchar_fd((char)va_arg(curr_varr, int), 1);
	else if (c == '%')
		sum = write(1, &c, 1);
	else if (c == 'x')
		sum = ft_convert((unsigned int)va_arg(curr_varr, unsigned int), 16, 1, 0);
	else if (c == 'X')
		sum = ft_convert((unsigned int)va_arg(curr_varr, unsigned int), 16, 0, 0);
	else if (c == 'u') 
		sum = ft_u_putnbr_fd((unsigned int)va_arg(curr_varr, unsigned int), 1, sum, &sum);
	else if (c == 'p') 
		sum = ft_convert((unsigned long)va_arg(curr_varr, unsigned long), 16, 1, 1);
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
		if (*format == '%')
		{
			sum += whichspecifier(*(format + 1), input);
			format++;
		}
		else if (*format == 10)
		{
			write(1, "\n", 1);
			sum++;
		}
		else
			sum += write(1, format, 1);
		++format;
	}
	va_end(input);
	return (sum);
}

int	main(void)
{
	long long	num = 3545312332;
	int len1, len2;
	void *s = &num;
	len1 = 0;
	len2 = 0;
	len1 = ft_printf("%p", s);
	ft_printf("\n");
	len2 = printf("%p", s);
	if (len1 == len2)
		printf("\n\033[0;32mCORRECT\033[0m");
	else
		printf("\033[0;31m\nINCORRECT GOT: %d EXP: %d\n\033[0m", len1, len2);
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
Printf future features:
	//////////////////////////////////////
	//									//
	//		  Character Sequence		//	
	//									//
	//////////////////////////////////////
	"%n$" where n is the argument number we want to print. e.g.:
	main():	
		int a = 10;
		int b = 20;
		int c = 30;
		printf("%3$d %1$d %2$d\n", a, b, c);
	Output:
		30 10 20
	//////////////////////////////////////
	//									//
	//		  Field width				//	
	//									//
	//////////////////////////////////////
	- (%n{specifier}) field widths where the syntax is "%n{specifier}", e.g., "%10d" which will
	print the integer with at aleast 10 characters (being spaces) padding. If the 'n' number 
	given is less than the number of digits of the int given, then printf will ignore it. e.g.:
	main():
		int num = 123;
		printf("%3d\n", num);
		printf("%7d\n", num);
	
		int num = 123;
		printf("%-10d", num);
		printf("------");
		printf("%10d", num);
	output:
	""123
	"    "123
	"123       ------       123"	
	//////////////////////////////////////
	//									//
	//		  	Precision				//	
	//									//
	//////////////////////////////////////
	- gives the minimum number of digits to appear for the d, i, o, u, x, and X 
	conversion specifiers
*/