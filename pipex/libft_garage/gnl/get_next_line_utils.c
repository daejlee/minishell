/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:04:51 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/28 15:04:52 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

t_list	*g_lstnew(int fd)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->fd = fd;
	ptr->next = NULL;
	ptr->str = NULL;
	ptr->last_ret = NULL;
	ptr->fst_call = 1;
	ptr->eof_flag = 0;
	return (ptr);
}

void	*g_lstdel(t_list **targ_adr, char *buf, t_list **head_adr)
{
	t_list	*target;

	if (buf)
		free (buf);
	if (!targ_adr || !head_adr || !*targ_adr || !*head_adr)
		return (NULL);
	target = *targ_adr;
	if (*targ_adr == *head_adr)
		*head_adr = target->next;
	else
	{
		*targ_adr = *head_adr;
		while ((*targ_adr)->next != target)
				*targ_adr = (*targ_adr)->next;
		(*targ_adr)->next = target->next;
	}
	if (target->str)
		free (target->str);
	target->last_ret = NULL;
	target->str = NULL;
	free (target);
	target = NULL;
	return (NULL);
}

unsigned int	g_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

unsigned int	g_strlcpy(char *dst, const char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while ((i + 1 < size) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*concat_buf(char *str, char *buf, int r_flag)
{
	unsigned int	i;
	char			*ret;

	if (!str)
	{
		ret = (char *)malloc(r_flag + 1);
		if (!ret)
			return (NULL);
		g_strlcpy(ret, buf, r_flag + 1);
	}
	else
	{
		ret = (char *)malloc(g_strlen(str) + r_flag + 1);
		if (!ret)
			return (NULL);
		g_strlcpy(ret, str, g_strlen(str) + 1);
		g_strlcpy(ret + g_strlen(str), buf, r_flag + 1);
		free (str);
	}
	i = 0;
	while (i < BUFFER_SIZE + 1)
		buf[i++] = 0;
	return (ret);
}
