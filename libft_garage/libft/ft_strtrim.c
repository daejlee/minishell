/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:46 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/30 17:21:24 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_set(char c, char const *set)
{
	unsigned int	j;

	j = 0;
	while (set[j])
	{
		if (c != set[j])
			j++;
		else
			return (1);
	}
	return (0);
}

static unsigned int	trim_beginning(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (is_set(s1[i], set) == 1)
			i++;
		else
			return (i);
	}
	return (i);
}

static int	is_it_end_of_str(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (is_set(s1[i], set) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

static unsigned int	trim_last(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (is_set(s1[i], set) == 0)
			i++;
		else
		{
			if (is_it_end_of_str(&s1[i], set))
				return (i - 1);
			else
				i++;
		}
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*res;
	unsigned int	len;

	if (!s1)
		return (0);
	i = trim_beginning(s1, set);
	j = trim_last(&s1[i], set);
	len = j + 1;
	j = 0;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	while (len > 0)
	{
		res[j] = s1[i + j];
		j++;
		len--;
	}
	res[j] = '\0';
	return (res);
}
