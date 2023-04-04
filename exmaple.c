# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int ft_hex_putstr(char *s, int fd, int length, int ptr)
{
    int sum = 0;

    if (!s)
        return 0;
    if (ptr)
        sum += write(fd, "0x", 2);
    printf("here\n");
	while (length >= 0)
	{
		sum += write(fd, s[length], length);

	}
    return sum;
}

int ft_hex_length(unsigned long num, int base)
{
    int length = 0;
    while (num != 0)
    {
        num /= base;
        length++;
    }
    return length;
}

int ft_convert(unsigned long num, int base, int low, int ptr)
{
    char *uphexi = "0123456789ABCDEF";
    char *p_str;
    char *final;
    int chck = 0;

    if (low)
        chck = 16;
    p_str = malloc(sizeof(char) * ft_hex_length(num, base) + 1);
    if (!p_str)
        return 0;
    final = p_str;
    while (num != 0)
    {
        *p_str = uphexi[num % base + chck];
        num /= base;
        p_str++;
    }
    *p_str = '\0';
    return ft_hex_putstr(final, 1, ft_hex_length(num, base), ptr);
}

unsigned int ft_pointer(unsigned long n, int fd, int total, int *sum)
{
    void *s = &n;
    unsigned long hex = (unsigned long)s;
    printf("%lu", hex);
    return (*sum + 1);
}

int main(void)
{
    unsigned int example = 111321321;
    void *s = &example;
    unsigned long hex = (unsigned long)s;
    printf("%p\n%lu\n", s, hex);
    ft_convert(hex, 16, 1, 1);
    return 0;
}
