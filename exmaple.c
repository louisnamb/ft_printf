# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
/*
void convert(unsigned int num, int base)
{ 
	if(num)
	{
		convert(num/base);
		printf("%c","0123456789ABCDEF"[num%base]);
	}
}*/

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

int	ft_hex_putstr(char *s, int fd, int length)
{
	int	sum;

	sum = 0;
	if (!s)
		return (0);
	while (length >= 0)
	{
		sum += write(fd, &s[length], 1);
		length--;
	}
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

int main()
{
    char    *uphexi;
    int        chck;
    int        strnum;
    int low = 1;
    int num = 346791;
	int number = num;
    int base = 16;
    strnum = ft_hex_length(num, base);
    chck = 0;
    uphexi = "0123456789ABCDEF0123456789abcdef";
    if (low)
        chck = 16;
	char *p_str = (char *)malloc(sizeof(char) * strnum + 1);
    char *final = p_str;
	while (num != 0)
    {
        *p_str++ = uphexi[num % base + chck];
        printf("%c", *p_str);
        num /= base;
    }
	*p_str = '\0';
    printf("\n%x\n", 346791);
    ft_hex_putstr(final, 1, strnum);
    return (0);
}