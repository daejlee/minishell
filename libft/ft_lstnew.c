/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:51:45 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 03:02:08 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lib_list	*ft_lstnew(void *content)
{
	t_lib_list	*ptr;

	ptr = (t_lib_list *)malloc(sizeof(t_lib_list));
	if (ptr == 0)
		return (0);
	ptr->content = content;
	ptr->next = 0;
	return (ptr);
}
