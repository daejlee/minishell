/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_no_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:21:01 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 22:21:08 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	zero_with_precision(struct s_info *p, unsigned int i)
{
	p->res_str[i] = '\0';
	if (ft_strchr(p->flag, '0'))
	{
		p->res_str[i++] = ' ';
		p->res_str[i] = '\0';
	}
}

void	num_no_padding(struct s_info *p, int raw_strlen)
{
	unsigned int	i;

	i = 0;
	if (ft_strchr(p->flag, '+') && !ft_strchr("+-", p->raw_str[0]))
		p->res_str[i++] = '+';
	else if (ft_strchr(p->flag, ' ') && !ft_strchr("+-", p->raw_str[0]))
		p->res_str[i++] = ' ';
	if (ft_strchr(p->flag, '#') && p->spc == 'x' && p->raw_str[0] != '0')
	{
		ft_strlcpy(&p->res_str[i], "0x", 3);
		i += 2;
	}
	else if (ft_strchr(p->flag, '#') && p->spc == 'X' && p->raw_str[0] != '0')
	{
		ft_strlcpy(&p->res_str[i], "0X", 3);
		i += 2;
	}
	if ((p->precision == -2 || p->precision == 0) && p->raw_str[0] == '0')
		zero_with_precision(p, i);
	else
		ft_strlcpy(&p->res_str[i], p->raw_str, raw_strlen + 1);
}
