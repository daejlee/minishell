/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:14 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/30 13:46:50 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*temp;
	char	a;

	i = 0;
	a = (char)c;
	temp = (char *)s;
	while (i < n)
	{
		if (temp[i] == a)
			return (&temp[i]);
		else
			i++;
	}
	return (0);
}
