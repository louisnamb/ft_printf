/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:43:45 by lnambaji          #+#    #+#             */
/*   Updated: 2023/03/31 13:52:05 by lnambaji         ###   ########.fr       */
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
	int	len;

	len = ft_strlen(s);
	if (!s || !fd)
		return (0);
	printf("ft_putstr_fd = %s\n", s);
	return (write(fd, &*s, len));
}

int	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (0);
	return (write(fd, &c, 1));
}

int    ft_putnbr_fd(int n, int fd, int total, int *sum)
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
	if (c == 'd')
		sum = ft_putnbr_fd((int)va_arg(curr_varr, int), 1, sum, &sum);
	else if (c == 's')
		sum = ft_putstr_fd((char *)va_arg(curr_varr, char *), 1);
	else if (c == 'c')
		sum = ft_putchar_fd((char)va_arg(curr_varr, int), 1);
	else if (c == '%')
		sum = write(1, &c, 1);
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
		if (*format == '%')
		{
			sum += whichspecifier(*(format + 1), input);
			format++;
		}
		else if (*format == 10)
		{
			write(1, "\n", 1);
			sum += 2;
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
	char *str = "hello";
	int len1, len2;

	len1 = 0;
	len2 = 0;
	len1 = ft_printf("%d", -433);
	printf("\n");
	len2 = printf("%d", -433);
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

*/