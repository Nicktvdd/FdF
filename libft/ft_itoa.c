/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:42:41 by nvan-den          #+#    #+#             */
/*   Updated: 2022/12/12 15:06:34 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(long n)
{
	int	len;

	len = 0;
	while (n / 10)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

static char	*ft_positive(long n, int len, char *str)
{
	while (--len >= 0)
	{
		str[len] = (n % 10 + '0');
		n = n / 10;
	}
	return (str);
}

static char	*ft_negative(long n, int len, char *str)
{
	if (n <= -2147483648)
	{
		n = -214748364;
		str[--len] = '8';
	}
	n *= -1;
	while (--len > 0)
	{
		str[len] = (n % 10 + '0');
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(long n)
{
	int		i;
	int		len;
	char	*str;

	len = ft_counter(n);
	i = len;
	if (n < 0)
		len++;
	(str = malloc(sizeof(char) * (len + 1)));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = ('-');
		i++;
		ft_negative(n, len, str);
	}
	else
		ft_positive(n, len, str);
	str[i] = '\0';
	return (str);
}
