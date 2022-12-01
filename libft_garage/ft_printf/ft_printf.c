/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:19:59 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:20:04 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static unsigned int	count_per(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] == '\%')
		i++;
	return (i);
}

static int	print_str_until_per(unsigned int *outer_i, const char *str)
{
	unsigned int	i;
	int				res;

	i = 0;
	res = 0;
	while (str[i] != '\%')
	{
		ft_putchar_fd(str[i++], 1);
		res++;
		if (str[i] == '\0')
			break ;
	}
	*outer_i += i;
	return (res);
}

static int	print_per(unsigned int *outer_i, const char *str)
{
	unsigned int	per_count;
	int				res;
	unsigned int	i;

	i = 0;
	res = 0;
	per_count = (count_per(&str[i]) / 2);
	while (per_count)
	{
		i += 2;
		ft_putchar_fd('\%', 1);
		res++;
		per_count--;
	}
	*outer_i += i;
	return (res);
}

int	ft_printf(const char *str, ...)
{
	va_list			ap;
	unsigned int	i;
	int				res;
	struct s_info	*p;

	i = 0;
	res = 0;
	va_start(ap, str);
	while (str[i])
	{
		res += print_str_until_per(&i, &str[i]);
		res += print_per(&i, &str[i]);
		if (str[i] == '\%')
		{
			i++;
			p = (struct s_info *)malloc(sizeof(struct s_info));
			if (p == 0)
				return (0);
			i += collect_format(&str[i], p, ap);
			p->res_str = process_raw_str(p);
			res += print_res_str(p);
		}
	}
	return (res);
}
