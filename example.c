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
	int	i;

	i = 0;
	sum = 0;
	if (!s)
		return (0);
    while (length >= 0)
    {
        sum += write(fd, &s[length], 1);
        length--;
    }
//	sum += write(fd, &s[length], 1);
	return (sum);
}

int	ft_hexlen(unsigned long num, int base)
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

char *ptrmkr(char *ptr, unsigned long num)
{
	if (num == 0)
		ptr[2] = '0';
	return (ptr);
}

int	ft_convert(unsigned long num, int base, int low, int ptr)
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
	p_str = malloc(sizeof(char) * (ft_hexlen(num, base) + 2) + (2 * ptr));
	if (!p_str)
		return (0);
	if (num == 0)
	{
		printf("inside if\n");
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
	sum += ft_hex_putstr(p_str, 1, i, ptr);
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
		s = ft_u_putnbr_fd((unsigned int)va_arg(var, unsigned int), 1, s, &s);
	else if (c == 'p')
	{
		s += write(1, "0x", 2);
		s = ft_convert((unsigned long)va_arg(var, unsigned long), 16, 16, 1);
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
	/*if (ft_printf(" %x ", 0) == printf(" %x ", 0))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("1 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 0), printf(" %x ", 0));
    if (ft_printf(" %x ", -1) == printf(" %x ", -1))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("2 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -1), printf(" %x ", -1));
	if (ft_printf(" %x ", 1) == printf(" %x ", 1))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("3 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 1), printf(" %x ", 1));
	if (ft_printf(" %x ", 9) == printf(" %x ", 9))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("4 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 9), printf(" %x ", 9));
	if (ft_printf(" %x ", 10) == printf(" %x ", 10))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("5 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 10), printf(" %x ", 10));
	if (ft_printf(" %x ", 11) == printf(" %x ", 11))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("6 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 11), printf(" %x ", 11));  
	if (ft_printf(" %x ", 15) == printf(" %x ", 15))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("7 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 15), printf(" %x ", 15));
	if (ft_printf(" %x ", 16) == printf(" %x ", 16))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("8 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 16), printf(" %x ", 16));
	if (ft_printf(" %x ", 17) == printf(" %x ", 17))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("9 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 17), printf(" %x ", 17));
	if (ft_printf(" %x ", 99) == printf(" %x ", 99))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("10  \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 99), printf(" %x ", 99));
	if (ft_printf(" %x ", 100) == printf(" %x ", 100))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("11  \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 100), printf(" %x ", 100));
	if (ft_printf(" %x ", 101) == printf(" %x ", 101))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("12 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 101), printf(" %x ", 101));
	if (ft_printf(" %x ", -9) == printf(" %x ", -9))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("13 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -9), printf(" %x ", -9));
	if (ft_printf(" %x ", -10) == printf(" %x ", -10))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("14 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -10), printf(" %x ", -10));
	if (ft_printf(" %x ", -11) == printf(" %x ", -11))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("15 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 11), printf(" %x ", 11));
	if (ft_printf(" %x ", -14) == printf(" %x ", -14))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("16 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -14), printf(" %x ", -14));
	if (ft_printf(" %x ", -15) == printf(" %x ", -15))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("17 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -15), printf(" %x ", -15));
	if (ft_printf(" %x ", -16) == printf(" %x ", -16))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("18 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -16), printf(" %x ", -16));
	if (ft_printf(" %x ", -99) == printf(" %x ", -99))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("19 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -99), printf(" %x ", -99));
	if (ft_printf(" %x ", -100) == printf(" %x ", -100))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("20 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -100), printf(" %x ", -100));
	if (ft_printf(" %x ", -101) == printf(" %x ", -101))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("21 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -101), printf(" %x ", -101));
	if (ft_printf(" %x ", INT_MAX) == printf(" %x ", INT_MAX))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("22 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", INT_MAX), printf(" %x ", INT_MAX));
	if (ft_printf(" %x ", INT_MIN) == printf(" %x ", INT_MIN))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("23 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", INT_MIN), printf(" %x ", INT_MIN));
	if (ft_printf(" %x ", LONG_MAX) == printf(" %x ", LONG_MAX))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf(" \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", LONG_MAX), printf(" %x ", LONG_MAX));
	if (ft_printf(" %x ", LONG_MIN) == printf(" %x ", LONG_MIN))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf(" \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", LONG_MIN), printf(" %x ", LONG_MIN)); 
	if (ft_printf(" %x ", UINT_MAX) == printf(" %x ", UINT_MAX))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("24 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", UINT_MAX), printf(" %x ", UINT_MAX)); 
	if (ft_printf(" %x ", ULONG_MAX) == printf(" %x ", ULONG_MAX))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf(" \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", ULONG_MAX), printf(" %x ", ULONG_MAX)); 
	if (ft_printf(" %x ", 9223372036854775807LL) == printf(" %x ", 9223372036854775807LL))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf(" \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 9223372036854775807LL), printf(" %x ", 9223372036854775807LL));
	int len1 = ft_printf(" %x %x %x %x", INT_MAX, INT_MIN, 0, -42);
	printf("\n\nreal:");
	int len2 = printf(" %x %x %x %x", INT_MAX, INT_MIN, 0, -42);
	if (len1 == len2)
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("\n\n\033[0;31m\n25 INCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x %x %x %x", INT_MAX, INT_MIN, 0, -42), printf(" %x %x %x %x", INT_MAX, INT_MIN, 0, -42)); 
    if (ft_printf(" %x ", 42) == printf(" %x ", 42))
    	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("26 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", 42), printf(" %x ", 42)); 
	if (ft_printf(" %x ", -42) == printf(" %x ", -42))
        	printf("\n \033[0;32mCORRECT \033[0m");
	else
		printf("27 \033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", ft_printf(" %x ", -42), printf(" %x ", -42));
    len1 = ft_printf("%x %x", 0, -42);
	len2 = printf("%x %x", 0, -42);
	printf("\n\n");
	if (len1 == len2)
		printf("correct\n");
	else
		printf("wrong, exp: %d got: %d", len2, len1);*/
	int len1, len2;
	printf("\n");
	int arr[5] = {1, -1, 15, 16, 17};
	int i = 0;
	long num = 7466538256166632996;
	void *ptr = &num;
	len1 = ft_printf(".tQ\t6s549rI%p@wCZm'n_'", ptr);
	printf("\n");
	len2 = printf(".tQ\t6s549rI%p@wCZm'n_'", ptr);
	if (len1 == len2)
		printf("\n\033[0;32mCORRECT \033[0m EXP:%d\n", len2);
	else
		printf("\033[0;31m\nINCORRECT GOT: %d EXP: %d\n \033[0m\n", len1, len2);
	return 0;
}