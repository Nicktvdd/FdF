/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:27:44 by nvan-den          #+#    #+#             */
/*   Updated: 2022/11/03 10:58:44 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*c;
	unsigned char	*h;

	c = (unsigned char *)s1;
	h = (unsigned char *)s2;
	i = 0;
	j = 0;
	while (j < n)
	{
		if (c[i] == h[i])
			i++;
		j++;
	}
	if (i == j)
		return (0);
	else if (c[i] - h[i] == 0)
		return (sizeof(c[i]));
	else
		return (c[i] - h[i]);
}
