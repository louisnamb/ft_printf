/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:54:28 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/06 13:20:35 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 32
# endif

unsigned int	ft_u_putnbr_fd(unsigned int n, int fd, int total, int *sum);

int				ft_hex_putstr(char *s, int fd, int length, int ptr);

int				ft_hex_length(unsigned long num, int base);

int				ft_convert(unsigned long num, int base, int low, int ptr);

size_t			ft_strlen(const char *s);

int				ft_putstr_fd(char *s, int fd);

int				ft_putchar_fd(char c, int fd);

int				ft_putnbr_fd(int n, int fd, int total, int *sum);

int				whichspecifier(const char c, va_list curr_varr);

int				ft_printf(const char *format, ...);

#endif
