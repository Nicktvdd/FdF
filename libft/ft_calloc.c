/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:58:56 by nvan-den          #+#    #+#             */
/*   Updated: 2022/11/09 15:47:05 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*string;

	if (count == 0 || size == 0)
	{
		string = malloc(1);
		if (!string)
			return (0);
		return (string);
	}
	if (count * size % size)
		return (0);
	else
		string = malloc(size * count);
	if (string)
		ft_bzero(string, size * count);
	return (string);
}
