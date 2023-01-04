/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:48 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/30 15:02:28 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*res;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	i = 0;
	while (i < len && start + i < s_len)
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (res == 0)
		return (0);
	i = 0;
	while (i < len && (start + i < s_len))
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
