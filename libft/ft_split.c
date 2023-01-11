/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:31:10 by nvan-den          #+#    #+#             */
/*   Updated: 2022/11/07 16:16:42 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*ft_strinsert(const char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(*s) * (ft_len(s, c) + 1));
	if (str == NULL)
		return (0);
	while (s[i] != c && s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_stringcounter(const char *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			counter++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**array;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	array = malloc(sizeof(s) * (ft_stringcounter(s, c) + 1));
	if (array == NULL)
		return (NULL);
	while (j < ft_stringcounter(s, c))
	{
		while (s[i] == c && s[i] != '\0')
		{
			i++;
		}
		array[j] = ft_strinsert(&s[i], c);
		i += ft_len(&s[i], c);
		j++;
	}
	array[j] = NULL;
	return (array);
}
