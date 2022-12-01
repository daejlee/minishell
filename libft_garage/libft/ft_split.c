/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:27 by daejlee           #+#    #+#             */
/*   Updated: 2022/04/23 19:06:31 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	malloc_by_wd(char **res, char const *s,
		char c, unsigned int wd_count)
{
	unsigned int	wd_size;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < wd_count)
	{
		wd_size = 0;
		while (s[j] == c && s[j])
			j++;
		while (s[j] != c && s[j])
		{
			wd_size++;
			j++;
		}
		res[i] = (char *)malloc(sizeof(char) * (wd_size + 1));
		if (res[i] == 0)
			return (1);
		i++;
	}
	res[i] = 0;
	return (0);
}

static void	purge(char **res)
{
	unsigned int	i;

	i = 0;
	while (*res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

void	make_arr(char const *s, char c, char **res)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	while (1)
	{
		while (s[j] == c && s[j])
			j++;
		if (s[j] == '\0')
			break ;
		k = 0;
		while (s[j] != c && s[j])
		{
			res[i][k] = s[j];
			j++;
			k++;
		}
		res[i][k] = '\0';
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	unsigned int	wd_count;
	unsigned int	i;
	char			**res;

	if (!s)
		return (NULL);
	i = 0;
	wd_count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			wd_count++;
		while (s[i] != c && s[i])
			i++;
	}
	res = (char **)malloc(sizeof(char *) * (wd_count + 1));
	if (!res)
		return (NULL);
	if (malloc_by_wd(res, s, c, wd_count) == 1)
		purge(res);
	make_arr(s, c, res);
	return (res);
}
