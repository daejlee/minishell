/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:50:52 by daejlee           #+#    #+#             */
/*   Updated: 2022/03/30 13:50:54 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_lib_list *lst, void (*f)(void *))
{
	t_lib_list	*add;

	if (!lst || !f)
		return ;
	add = lst;
	while (1)
	{
		f(add->content);
		if (add->next != 0)
			add = add->next;
		else
			break ;
	}
}
