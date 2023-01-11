/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:47:47 by nvan-den          #+#    #+#             */
/*   Updated: 2022/11/09 12:58:10 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*c;
	unsigned char	*h;

	if (n > 9223372036854775807LL)
		return (n);
	c = (unsigned char *)s1;
	h = (unsigned char *)s2;
	i = 0;
	j = 0;
	while (j < n && (s1[i] || s2[i] != '\0'))
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
