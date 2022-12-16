/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:45 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/23 15:31:18 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int		i;
	char				*res;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			res = (char *)&s[i];
			while (1)
			{
				i++;
				if (s[i] == (unsigned char)c)
					break ;
				else if (s[i] == '\0')
					return (res);
			}
		}
		else
			i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	else
		return (0);
}
