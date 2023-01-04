/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:02 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/30 14:36:45 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;

	if (nmemb && size)
	{
		if (size > SIZE_MAX / nmemb)
			return (NULL);
	}
	arr = (char *)malloc(nmemb * size);
	if (arr == 0)
		return (0);
	ft_bzero(arr, nmemb * size);
	return ((void *)arr);
}
