/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:17 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/23 13:28:41 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*d;
	char			*s;

	if (n == 0 || (src == 0 && dest == 0))
		return (dest);
	d = (char *)dest;
	s = (char *)src;
	if (s >= d)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (--n > 0)
			d[n] = s[n];
		d[n] = s[n];
	}
	return (dest);
}
