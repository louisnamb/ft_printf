# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int	ft_hex_putstr(char *s, int fd, int length, int ptr)
{
	int	sum;

	sum = 0;
	if (!s)
		return (0);
	if (ptr)
		sum += write(fd, "0x7ffe", 6);
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

unsigned int    ft_pointer(unsigned long n, int fd, int total, int *sum)
{
	unsigned long	example = 3515;
	void *s;
	s = &example;
	
	unsigned long hex = (unsigned long)s;
	printf("%lu", hex);
    return (*sum + 1);
}

int main(void)
{
	unsigned int	example = 111321321;
	void *s;
	s = &example;
	
	unsigned int hex = (unsigned int)s;
	printf("%p\n%u\n", s, hex);
	ft_convert(hex, 16, 1, 1);
	return 0;
}