/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:19:36 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:19:38 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_precision(const char *str, va_list ap)
{
	unsigned int	i;
	int				res;

	i = 0;
	if (str[i] == '.')
	{
		if (str[1] >= '0' && str[1] <= '9')
			res = ft_atoi(&str[1]);
		else if (str[1] == '*')
			res = va_arg(ap, int);
		else
			res = -2;
	}
	else
		res = -1;
	return (res);
}
