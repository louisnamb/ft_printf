/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:07:22 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/06 10:20:42 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

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