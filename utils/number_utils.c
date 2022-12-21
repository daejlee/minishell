/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:06:29 by hkong             #+#    #+#             */
/*   Updated: 2022/12/21 16:09:48 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_numbers(size_t *num1, size_t *num2, \
												size_t *num3, size_t *num4)
{
	if (num1)
		*num1 = 0;
	if (num2)
		*num2 = 0;
	if (num3)
		*num3 = 0;
	if (num4)
		*num4 = 0;
}

void	set_start_end(size_t *start, size_t *end, \
							size_t start_num, size_t end_num)
{
	if (start)
		*start = start_num;
	if (end)
		*end = end_num;
}
