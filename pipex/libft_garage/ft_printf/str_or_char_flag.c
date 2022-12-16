/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_or_char_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:21:35 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 22:21:36 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	str_or_char_flag(struct s_info *p, int raw_strlen)
{
	if (p->precision < raw_strlen && p->precision >= 0
		&& p->width > p->precision)
		p->padding = p->width - p->precision;
	if (p->precision < raw_strlen && p->precision >= 0)
	{
		ft_strlcpy(p->res_str, p->raw_str, p->precision + 1);
		ft_memset(&p->res_str[p->precision], ' ', p->padding);
	}
	else if (p->padding > 0)
	{
		ft_strlcpy(p->res_str, p->raw_str, raw_strlen + 1);
		ft_memset(&p->res_str[raw_strlen], ' ', p->padding);
	}
	else
		ft_strlcpy(p->res_str, p->raw_str, raw_strlen + 1);
}
