/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:51:54 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 03:02:13 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_lib_list *lst)
{
	int			count;
	t_lib_list	*add;

	if (lst == 0)
		return (0);
	count = 1;
	add = lst->next;
	while (1)
	{
		if (add != 0)
		{
			count++;
			add = add->next;
		}
		else
			return (count);
	}
}
