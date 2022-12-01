/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:26:54 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/30 14:31:05 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static const char	*blank_check(const char *nptr)
{
	unsigned int	i;

	i = 0;
	while ((nptr[i] >= 8 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	return (&nptr[i]);
}

static int	outlier_check(unsigned int res, int sign)
{
	if (res > 2147483648 && sign == -1)
		return (0);
	else if (res > 2147483647 && sign == 1)
		return (-1);
	else
		return (res * sign);
}

int	ft_atoi(const char *nptr)
{
	int					sign;
	unsigned int		i;
	unsigned int		res;

	nptr = blank_check(nptr);
	sign = 1;
	i = 0;
	res = 0;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	res = outlier_check(res, sign);
	return (res);
}
