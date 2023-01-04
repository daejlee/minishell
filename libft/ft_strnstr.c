/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:43 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/23 19:12:23 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	find_wd(const char *s1, const char *s2, unsigned int i,
	unsigned int n)
{
	unsigned int	j;

	j = 0;
	while (1)
	{
		if (i < n && s1[j] && s1[j] == s2[j])
		{
			if (s2[j + 1] == '\0')
				return (1);
			j++;
			i++;
		}
		else
			break ;
	}
	return (0);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	char			*res;

	if (*s2 == '\0')
		return ((char *)s1);
	i = 0;
	while (i < n && s1[i])
	{
		if (s1[i] == s2[0])
		{
			res = (char *)&s1[i];
			if (find_wd(&s1[i], s2, i, n) == 1)
				return (res);
			else
				i++;
		}
		else
			i++;
	}
	return (0);
}
