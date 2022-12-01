/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:32:45 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 20:33:03 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static unsigned int	get_width(struct s_info *p)
{
	unsigned int	i;
	char			*temp;

	temp = ft_itoa(p->width);
	i = ft_strlen(temp);
	free(temp);
	return (i);
}

static unsigned int	get_precision(struct s_info *p)
{
	unsigned int	i;
	char			*temp;

	temp = ft_itoa(p->precision);
	i = ft_strlen(temp) + 1;
	free(temp);
	return (i);
}

int	collect_format(const char *str, struct s_info *p, va_list ap)
{
	unsigned int	i;

	i = 0;
	p->flag = check_flag(&str[i]);
	if (p->flag != 0)
		i += ft_strlen(p->flag);
	p->width = check_width(&str[i], ap);
	if (p->width != -1)
		i += get_width(p);
	p->precision = check_precision(&str[i], ap);
	if (p->precision != -1 && p->precision != -2)
		i += get_precision(p);
	else if (p->precision == -2)
		i++;
	p->raw_str = check_specifier(ap, &str[i]);
	p->spc = str[i++];
	return (i);
}
