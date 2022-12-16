/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:20:15 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:20:19 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

char	*ft_write_d(va_list ap)
{
	char	*str;
	int		val;

	val = va_arg(ap, int);
	str = ft_itoa(val);
	if (str == 0)
		return (0);
	return (str);
}
