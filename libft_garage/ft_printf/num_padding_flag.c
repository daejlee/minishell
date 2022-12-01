/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_padding_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:21:11 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 22:21:13 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	p_num_overprecision(struct s_info *p, int slots, unsigned int i)
{
	ft_memset(&p->res_str[i], '0', p->precision - slots);
	i += p->precision - slots;
	ft_strlcpy(&p->res_str[i], p->raw_str, slots + 1);
	i += slots;
	if (p->width > (int)ft_strlen(p->res_str))
		ft_memset(&p->res_str[i], ' ', p->width - ft_strlen(p->res_str));
}

static void	n_num_overprecision(struct s_info *p, int slots, unsigned int i)
{
	p->res_str[i++] = '-';
	ft_memset(&p->res_str[i], '0', p->precision - slots + 1);
	i += p->precision - slots + 1;
	ft_strlcpy(&p->res_str[i], p->raw_str + 1, slots);
	i += slots - 1;
	if (p->width > (int)ft_strlen(p->res_str))
		ft_memset(&p->res_str[i], ' ', p->width - ft_strlen(p->res_str));
}

static void	pad_without_precision(struct s_info *p, int slots,
				unsigned int i, unsigned int padding)
{
	if ((p->precision != -2 && p->precision != 0) || p->raw_str[0] != '0')
	{
		ft_strlcpy(&p->res_str[i], p->raw_str, slots + 1);
		i += slots;
	}
	if (ft_strchr(p->flag, '0'))
		ft_memset(&p->res_str[i], '0', padding);
	else
		ft_memset(&p->res_str[i], ' ', padding);
	if ((p->precision == -2 || p->precision == 0) && p->raw_str[0] == '0')
	{
		i += padding;
		if (ft_strchr(p->flag, '0'))
			p->res_str[i++] = '0';
		else
			p->res_str[i++] = ' ';
		p->res_str[i] = '\0';
	}
}

void	num_padding_flag(struct s_info *p, unsigned int padding, int slots)
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
	if (p->raw_str[0] != '-' && p->precision >= slots)
		p_num_overprecision(p, slots, i);
	else if (p->raw_str[0] == '-' && p->precision >= slots - 1)
		n_num_overprecision(p, slots, i);
	else
		pad_without_precision(p, slots, i, padding);
}
