/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:46:13 by nvan-den          #+#    #+#             */
/*   Updated: 2022/11/08 16:03:57 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	c = (char)c;
	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
	{
		str = &str[i];
		return (str);
	}
	else
		return (NULL);
}
