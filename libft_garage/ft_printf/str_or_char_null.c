/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_or_char_null.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:21:44 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 22:21:45 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	str_or_char_null(struct s_info *p, int raw_strlen)
{
	if (p->padding > 0 && ft_strchr(p->flag, '-'))
	{
		if (p->spc == 'c' || (p->spc == 's' && p->precision == -2))
			ft_strlcpy(p->res_str, "\0", raw_strlen + 1);
		else if (p->spc == 's')
			ft_strlcpy(p->res_str, "(null)", raw_strlen + 1);
		ft_memset(&p->res_str[raw_strlen], ' ', p->padding);
	}
	else if (p->padding > 0)
	{
		ft_memset(p->res_str, ' ', p->padding);
		if (p->spc == 'c' || (p->spc == 's' && p->precision == -2))
			ft_strlcpy(&p->res_str[p->padding], "\0", raw_strlen + 1);
		else if (p->spc == 's')
			ft_strlcpy(&p->res_str[p->padding], "(null)", raw_strlen + 1);
	}
	else
	{
		if (p->spc == 'c' || (p->spc == 's' && p->precision == -2))
			ft_strlcpy(p->res_str, "\0", raw_strlen + 1);
		else if (p->spc == 's')
			ft_strlcpy(p->res_str, "(null)", raw_strlen + 1);
	}
}
