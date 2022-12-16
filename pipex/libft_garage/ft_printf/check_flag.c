/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:19:31 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:20:59 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_c_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#'
		|| c == '0')
		return (1);
	else
		return (0);
}

char	*check_flag(const char *str)
{
	unsigned int	i;
	char			*res;

	i = 0;
	while (check_c_flag(str[i]))
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (res == 0)
		return (0);
	i = 0;
	while (check_c_flag(str[i]))
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
