/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:25 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/23 12:19:14 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>

static unsigned int	process_num(int n, int fd)
{
	unsigned int	num;

	if (n == 0)
	{
		write(fd, "0", 1);
		return (0);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		num = -n;
	}
	else
		num = n;
	return (num);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	unsigned int	num_temp;
	unsigned int	div;
	char			temp;

	div = 1;
	num = process_num(n, fd);
	if (num == 0)
		return ;
	num_temp = num;
	while (num_temp >= 10)
	{
		num_temp /= 10;
		div *= 10;
	}
	while (div > 0)
	{
		num_temp = num / div;
		temp = num_temp + '0';
		write(fd, &temp, 1);
		num -= num_temp * div;
		div /= 10;
	}
}
