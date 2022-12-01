/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:20:33 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:20:34 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./ft_printf.h"

static char	*get_res(unsigned int dig, unsigned long long val)
{
	char			*res;
	unsigned int	rem;
	unsigned int	i;

	res = (char *)malloc((dig + 1) * sizeof(char));
	if (res == 0)
		return (0);
	res[dig] = '\0';
	if (!val)
		res[2] = '0';
	i = 1;
	while (val)
	{
		rem = val % 16;
		val /= 16;
		res[dig - i++] = "0123456789abcdef"[rem];
	}
	res[0] = '0';
	res[1] = 'x';
	return (res);
}

char	*ft_write_p(va_list ap)
{
	unsigned long long		val;
	unsigned long long int	quo;
	unsigned int			dig;

	val = va_arg(ap, unsigned long long);
	quo = val;
	dig = 1;
	while (quo / 16)
	{
		quo /= 16;
		dig++;
	}
	dig += 2;
	return (get_res(dig, val));
}
