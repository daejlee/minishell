/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:20:23 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:20:25 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

char	*ft_write_i(va_list ap)
{
	char	*str;
	int		val;

	val = va_arg(ap, int);
	str = ft_itoa(val);
	if (str == 0)
		return (0);
	return (str);
}
