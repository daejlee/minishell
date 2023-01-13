/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:55:26 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 15:17:10 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "utils.h"

static int	seg_1(t_ft_export *p, t_env *env)
{
	int	i;

	p->size = 1;
	p->head = env;
	p->temp = p->head->next;
	while (p->temp != p->head)
	{
		p->size++;
		p->temp = p->temp->next;
	}
	p->arr = (t_env **)malloc(sizeof(t_env *) * p->size);
	if (!p->arr)
		return (print_error(MALLOC_FAIL, NULL));
	i = 0;
	p->temp = p->head;
	while (i < p->size)
	{
		p->arr[i++] = p->temp;
		p->temp = p->temp->next;
	}
	return (0);
}

static int	seg_2(t_ft_export p)
{
	int	i;

	i = 0;
	while (i < p.size)
	{
		if (ft_strncmp(p.arr[i]->key, "_", ft_strlen(p.arr[i]->key)))
		{
			write(1, "declare -x ", 12);
			write(1, p.arr[i]->key, ft_strlen(p.arr[i]->key));
			if (p.arr[i]->value)
			{
				write(1, "=\"", 3);
				write(1, p.arr[i]->value, ft_strlen(p.arr[i]->value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		i++;
	}
	free(p.arr);
	return (0);
}

int	print_sorted_env(t_env *env)
{
	t_ft_export		p;

	if (seg_1(&p, env))
		return (1);
	p.k = 0;
	while (p.k < p.size)
	{
		p.i = 0;
		while (p.i < p.size - 1)
		{
			if (ft_strlen(p.arr[p.i]->key) <= ft_strlen(p.arr[p.i + 1]->key))
				p.len = ft_strlen(p.arr[p.i + 1]->key);
			else
				p.len = ft_strlen(p.arr[p.i]->key);
			if (ft_strncmp(p.arr[p.i]->key, p.arr[p.i + 1]->key, p.len) > 0)
			{
				p.temp = p.arr[p.i];
				p.arr[p.i] = p.arr[p.i + 1];
				p.arr[p.i + 1] = p.temp;
			}
			p.i++;
		}
		p.k++;
	}
	return (seg_2(p));
}
