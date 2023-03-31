/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:54:28 by lnambaji          #+#    #+#             */
/*   Updated: 2023/03/30 14:47:14 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
//#include "libft.h"

int		ft_printf(const char *format, ...);
int		printconversions(const char *conversions);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);