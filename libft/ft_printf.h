/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:24:10 by nvan-den          #+#    #+#             */
/*   Updated: 2023/01/17 15:20:59 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

int	ft_printf(const char *str, ...);
int	sudi_params(const char *str, va_list ap);
int	ft_strrev(char *src, char flag);
int	ft_hex(unsigned long long deci, char flag);
int	params(const char *str, va_list ap);

#endif