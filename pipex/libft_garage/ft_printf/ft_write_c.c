/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:20:08 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:21:05 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

char	*ft_write_c(va_list ap)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	if (str == 0)
		return (0);
	str[0] = va_arg(ap, int);
	str[1] = '\0';
	return (str);
}
