/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:10:36 by nvan-den          #+#    #+#             */
/*   Updated: 2022/11/08 16:56:03 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_append(char const *s2, int i, char *newstr)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		newstr[i] = s2[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		s2size;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s2size = (sizeof(s2) * ft_strlen(s2));
	newstr = malloc((sizeof(s1) * ft_strlen(s1)) + s2size);
	if (newstr == NULL)
		return (NULL);
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	ft_append(s2, i, newstr);
	return (newstr);
}
