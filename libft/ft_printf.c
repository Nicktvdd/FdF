/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:34:30 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/17 15:21:01 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// deals with the s, u, d and i parameters
int	sudi_params(const char *str, va_list ap)
{
	char	*string;
	int		count;

	count = 0;
	if (*str == 's')
	{
		string = va_arg(ap, char *);
		if (string == NULL)
			count = write(1, "(null)", 6);
		else
			ft_putstr_fd(string, 1);
		count += ft_strlen(string);
	}
	else if (*str == 'd' || *str == 'i' || *str == 'u')
	{
		if (*str == 'u')
			string = ft_itoa((unsigned int)va_arg(ap, unsigned int));
		else
			string = ft_itoa(va_arg(ap, int));
		ft_putstr_fd(string, 1);
		count = ft_strlen(string);
		free(string);
	}
	return (count);
}

// reverts the hexadecimal and prints it
int	ft_strrev(char *src, char flag)
{
	int		i;
	int		count;
	char	str[17];

	i = 0;
	count = strlen(src);
	while (count > 0)
	{
		str[--count] = src[i];
		i++;
	}
	str[i] = '\0';
	if (flag == 'p')
		ft_putstr_fd("0x", 1);
	ft_putstr_fd(str, 1);
	return (i);
}

// converts decimal to hexadecimal
int	ft_hex(unsigned long long deci, char flag)
{
	char			hexa[17];
	int				i;
	int				count;
	unsigned int	digit;

	i = 0;
	while (deci > 0)
	{
		digit = deci % 16;
		if (digit < 10)
			hexa[i++] = '0' + digit;
		else if (flag == 'X')
			hexa[i++] = 'A' + (digit - 10);
		else
			hexa[i++] = 'a' + (digit - 10);
		deci /= 16;
	}
	if (i == 0)
		hexa[i++] = '0';
	hexa[i] = '\0';
	count = ft_strrev(hexa, flag);
	if (flag == 'p')
		count += 2;
	return (count);
}

// take the argument from '%'
int	params(const char *str, va_list ap)
{
	int	count;

	count = 0;
	if (*str == 'c')
		ft_putchar_fd(va_arg(ap, int), 1);
	if (*str == 'c')
		count = 1;
	if (*str == 's')
		count = sudi_params(str, ap);
	if (*str == 'd' || *str == 'i' || *str == 'u')
		count = sudi_params(str, ap);
	if (*str == 'x' || *str == 'X')
		count = ft_hex(va_arg(ap, unsigned int), *str);
	if (*str == 'p')
		count = ft_hex(va_arg(ap, unsigned long long), *str);
	if (*str == '%')
		count = write(1, "%", 1);
	return (count);
}

// loop through the string until '%'
int	ft_printf(const char *str, ...)
{
	int			i;
	va_list		ap;
	int			count;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			count = count + params(&str[i], ap);
			i++;
		}
		else
		{
			count++;
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	va_end(ap);
	return (count);
}
