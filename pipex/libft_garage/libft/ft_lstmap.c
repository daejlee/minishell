/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:51:30 by daejlee           #+#    #+#             */
/*   Updated: 2022/04/23 20:35:54 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_lib_list	*ft_lstmap(t_lib_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		size;
	int		count;
	t_lib_list	*adr;

	if (!lst)
		return (0);
	count = 1;
	size = ft_lstsize(lst);
	adr = ft_lstnew(f(lst->content));
	if (adr == 0)
		return (0);
	while (count < size)
	{
		lst = lst->next;
		ft_lstadd_back(&adr, ft_lstnew(f(lst->content)));
		if (ft_lstlast(adr) == 0)
		{
			ft_lstclear(&adr, del);
			return (0);
		}
		count++;
	}
	return (adr);
}
