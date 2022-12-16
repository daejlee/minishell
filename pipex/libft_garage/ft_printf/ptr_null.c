/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_null.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:21:24 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 22:21:25 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ptr_null(struct s_info *p, int raw_strlen)
{
	if (p->padding > 0 && ft_strchr(p->flag, '-'))
	{
		ft_strlcpy(p->res_str, "0x0", raw_strlen + 1);
		ft_memset(&p->res_str[raw_strlen], ' ', p->padding);
	}
	else if (p->padding > 0)
	{
		ft_memset(p->res_str, ' ', p->padding);
		ft_strlcpy(&p->res_str[p->padding], "0x0", raw_strlen + 1);
	}
	else
		ft_strlcpy(p->res_str, "0x0", raw_strlen + 1);
}
