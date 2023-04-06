/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_libft.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:14:34 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/06 09:13:44 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 32
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

unsigned int    ft_u_putnbr_fd(unsigned int n, int fd, int total, int *sum)

int	ft_hex_putstr(char *s, int fd, int length, int ptr);

int	ft_hex_length(int num, int base);

int	ft_convert(unsigned int num, int base, int low, int ptr);

size_t	ft_strlen(const char *s);

int	ft_putstr_fd(char *s, int fd);

int	ft_putchar_fd(char c, int fd);

int	ft_putnbr_fd(int n, int fd, int total, int *sum);

int	whichspecifier(const char c, va_list curr_varr);

int	ft_printf(const char *format, ...);


#endif
