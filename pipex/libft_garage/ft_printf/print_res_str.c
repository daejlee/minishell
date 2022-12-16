/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_res_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:32:05 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 20:32:29 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	purge(struct s_info *p)
{
	if (p->flag)
		free(p->flag);
	if (p->spc != 's')
		free(p->raw_str);
	if (p->res_str)
		free(p->res_str);
	free(p);
}

int	print_res_str(struct s_info *p)
{
	int	res;

	ft_putstr_fd(p->res_str, 1);
	res = ft_strlen(p->res_str);
	if (p->raw_str)
	{
		if (!p->raw_str[0] && p->spc == 'c')
		{
			ft_putchar_fd('\0', 1);
			res++;
			if (!ft_strlen(p->res_str) && p->res_str[1])
			{
				ft_putstr_fd(&p->res_str[1], 1);
				res += ft_strlen(&p->res_str[1]);
			}
		}
	}
	purge(p);
	return (res);
}
