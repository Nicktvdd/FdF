/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:57:53 by nvan-den          #+#    #+#             */
/*   Updated: 2023/04/26 13:55:42 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_overflow(int min)
{
	if (min == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		min;

	i = 0;
	res = 0;
	min = 1;
	if (str == NULL)
		return(0);
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
	{
		min = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if (res < 0)
			return (ft_overflow(min));
	}
	return ((int)res * min);
}
