/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:51:11 by daejlee           #+#    #+#             */
/*   Updated: 2022/04/23 19:48:20 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_lib_list	*ft_lstlast(t_lib_list *lst)
{
	if (lst == 0)
		return (0);
	while (1)
	{
		if (lst->next != 0)
			lst = lst->next;
		else
			return (lst);
	}
}
