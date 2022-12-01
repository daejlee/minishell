/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_raw_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:20:54 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:20:55 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static char	*get_res(struct s_info *p, int slots)
{
	char	*res;

	if ((ft_strchr(p->flag, '+') || (ft_strchr(p->flag, ' ') && p->spc != 's'))
		&& p->raw_str[0] != '-')
		slots++;
	if (ft_strchr(p->flag, '#') && ft_strchr("xX", p->spc)
		&& p->raw_str[0] != '0')
		slots += 2;
	if (p->precision >= p->width && p->precision >= slots
		&& p->spc != 's')
	{
		p->padding = p->precision - slots;
		if (p->raw_str[0] == '-')
			p->padding++;
	}
	else if ((p->width > p->precision || (ft_strchr(p->flag, '-')
				&& p->spc == 's')) && p->width >= slots)
		p->padding = p->width - slots;
	res = (char *)malloc(sizeof(char) * (slots + p->padding + 1));
	if (res == 0)
		return (0);
	res[slots + p->padding] = '\0';
	return (res);
}

static char	*get_null_res(struct s_info *p, int slots)
{
	char	*res;

	if (p->width >= slots)
		p->padding = p->width - slots;
	if (p->precision >= slots && ft_strchr("pdiuxX", p->spc))
	{
		if (p->precision > p->width)
			p->padding += (p->precision - slots);
	}
	res = (char *)malloc(sizeof(char) * (slots + p->padding + 1));
	if (res == 0)
		return (0);
	res[slots + p->padding] = '\0';
	return (res);
}

static int	get_null_strlen(struct s_info *p)
{
	if (p->spc == 's' && p->precision == -2)
		return (0);
	else if (p->spc == 's')
	{
		p->raw_str = "(null)";
		return (6);
	}
	else if (p->spc == 'p')
		return (3);
	else
		return (1);
}

static void	assemble_res(struct s_info *p, int slots)
{
	if (ft_strchr("cs\%", p->spc))
	{
		if (!p->raw_str || (!p->raw_str[0] && p->spc == 'c')
			|| (p->precision == -2 && p->spc == 's'))
			str_or_char_null(p, slots);
		else if (p->raw_str[0] && ft_strchr(p->flag, '-'))
			str_or_char_flag(p, slots);
		else
			str_or_char_noflag(p, slots);
	}
	else
	{
		if (p->spc == 'p' && !p->raw_str)
			ptr_null(p, slots);
		else if (p->padding > 0 && ft_strchr(p->flag, '-'))
			num_padding_flag(p, p->padding, slots);
		else if (p->padding > 0)
			num_padding_noflag(p, p->padding, slots);
		else
			num_no_padding(p, slots);
	}
}

char	*process_raw_str(struct s_info *p)
{
	int				slots;
	int				raw_strlen;

	if (!p->raw_str || (!p->raw_str[0] && p->spc == 'c')
		|| (p->precision == -2 && p->spc == 's'))
		raw_strlen = get_null_strlen(p);
	else
		raw_strlen = ft_strlen(p->raw_str);
	slots = raw_strlen;
	p->padding = 0;
	if (!p->raw_str || (!p->raw_str[0] && p->spc == 'c')
		|| (p->precision == -2 && p->spc == 's'))
		p->res_str = get_null_res(p, slots);
	else
		p->res_str = get_res(p, slots);
	assemble_res(p, slots);
	return (p->res_str);
}
