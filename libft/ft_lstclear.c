/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:50:39 by daejlee           #+#    #+#             */
/*   Updated: 2022/04/23 14:46:54 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_lib_list **lst, void (*del)(void *))
{
	t_lib_list	*add;
	t_lib_list	*temp;

	add = *lst;
	temp = add;
	while (temp != 0)
	{
		add = add->next;
		ft_lstdelone(temp, del);
		temp = add;
	}
	*lst = 0;
}
