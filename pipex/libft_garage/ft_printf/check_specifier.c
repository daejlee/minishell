/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:19:46 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:19:47 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*check_specifier(va_list ap, const char *str)
{
	char	*res;

	if (*str == 'c')
		res = ft_write_c(ap);
	else if (*str == 's')
		res = ft_write_s(ap);
	else if (*str == 'p')
		res = ft_write_p(ap);
	else if (*str == 'd')
		res = ft_write_d(ap);
	else if (*str == 'i')
		res = ft_write_i(ap);
	else if (*str == 'u')
		res = ft_write_u(ap);
	else if (*str == 'x')
		res = ft_write_lowerx(ap);
	else if (*str == 'X')
		res = ft_write_upperx(ap);
	else if (*str == '\%')
		res = ft_write_per(ap);
	else
		return (0);
	return (res);
}
