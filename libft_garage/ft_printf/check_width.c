/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:19:51 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:19:56 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_width(const char *str, va_list ap)
{
	int	res;

	if (*str >= '0' && *str <= '9')
		res = ft_atoi(str);
	else if (*str == '*')
		res = va_arg(ap, int);
	else
		res = -1;
	return (res);
}
