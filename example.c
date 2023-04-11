#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
int	ft_putstr_fd(char *s, int fd)
{
	int sum;
	int len;

	len = 0;
	sum = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	else
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
		return (ft_putstr_fd("-2147483648", fd));
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

unsigned int	ft_uputnbr_fd(unsigned int n, int fd, int total, int *sum)
{
	if (n < 0)
	{
		total += ft_putchar_fd('-', fd);
		ft_uputnbr_fd(-n, fd, total, sum);
	}
	else if (n >= 10)
	{
		total++;
		ft_uputnbr_fd(n / 10, fd, total, sum);
		total += ft_putchar_fd(n % 10 + '0', fd);
	}
	else
	{
		*sum = total;
		total += ft_putchar_fd(n + '0', fd);
	}
	return (*sum + 1);
}

int	ft_hputstr(char *s, int fd, int length, int ptr)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	if (!s)
		return (0);
    while (length >= 1)
    {
        sum += write(fd, &s[length - 1], 1);
        length--;
    }
	return (sum);
}

int	ft_hexlen(signed long long int num, int base)
{
	int	length;
	int	add;

	length = 0;
	add = 0;
	while (num != 0)
	{
		num /= base;
		length++;
	}
	return (length);
}

char *ptrmkr(char *ptr, signed long long int num)
{
	char *dummy_ptr;

	dummy_ptr = ptr;
	dummy_ptr[0] = 48;
	dummy_ptr[1] = 120;
	if (num == 0)
		dummy_ptr[2] = '0';
	return (ptr);
}

int	ft_convert(signed long long int num, int base, int low, int ptr)
{
	char			*uphexi;
	char			*p_str;
	unsigned long	dummy;
	int				sum;
	int				i;

	sum = 0;
	dummy = num;
	i = 0;
	uphexi = "0123456789ABCDEF0123456789abcdef";
	p_str = malloc(sizeof(char) * (ft_hexlen(num, base) + 2));
	if (!p_str)
		return (0);
	if (num == 0)
	{
		ptrmkr(p_str, num);
		if (p_str[2] == 48)
			i++;
	}
	while (dummy != 0)
	{
		p_str[i] = uphexi[(dummy % base) + low];
		dummy /= base;
		i++;
	}
	p_str[i] = 0;
	sum += ft_hputstr(p_str, 1, i, ptr);
	free(p_str);
	return (sum);
}

int	whichspecifier(const char c, va_list var)
{
	int	s;

	s = 0;
	if (c == 'd' || c == 'i')
		s = ft_putnbr_fd((int)va_arg(var, int), 1, s, &s);
	else if (c == 's')
		s = ft_putstr_fd((char *)va_arg(var, char *), 1);
	else if (c == 'c')
		s = ft_putchar_fd((char)va_arg(var, int), 1);
	else if (c == '%')
		s = write(1, &c, 1);
	else if (c == 'x')
		s = ft_convert((unsigned long)va_arg(var, unsigned int), 16, 16, 0);
	else if (c == 'X')
		s = ft_convert((unsigned long)va_arg(var, unsigned int), 16, 0, 0);
	else if (c == 'u')
		s = ft_uputnbr_fd((unsigned int)va_arg(var, unsigned int), 1, s, &s);
	else if (c == 'p')
	{
		s += write(1, "0x", 2);
		s += ft_convert((unsigned long)va_arg(var, unsigned long), 16, 16, 1);
	}
	return (s);
}

int	ft_printf(const char *format, ...)
{
	va_list	input;
	int		sum;

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

int main(void)
{
	signed long long int num = LONG_MAX + 423856;
	unsigned long dummy = LONG_MAX + 423856;
	if (dummy == num)
		printf("equal\n");
	else
		printf("num: %llu dummy :%lu\n", num, dummy);
	printf("\n\n");
	int len1, len2;
	printf("\n");
	int arr[5] = {1, -1, 15, 16, 17};
	int i = 0;
	int *ptr = &i;
	len1 = ft_printf("%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	printf("\n");
	len2 = printf("%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	if (len1 == len2)
		printf("\n\033[0;32mCORRECT \033[0m EXP:%d\n", len2);
	else
		printf("\033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", len1, len2);
	return 0;
}