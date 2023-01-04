/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:01:41 by hkong             #+#    #+#             */
/*   Updated: 2023/01/04 18:09:53 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	syntax_error(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;

	token_num = meta->size;
	node = meta->head;
	while (token_num--)
	{
		if (node->type == PIPE)
		{
			if (token_num == meta->size - 1)
				return (print_error(SYNTAX_ERROR, node->str));
			if (!token_num)
				return (print_error(SYNTAX_ERROR, "newline"));
		}
		if (node->type == I_REDIR || node->type == I_HRDOC || \
					node->type == O_REDIR || node->type == O_APPND)
		{
			if (node->next->type == EMPTY)
				return (print_error(AMBIGUOUS_REDIR, node->next->origin_str));
			if (node->next->type != ARG)
				return (print_error(SYNTAX_ERROR, node->next->str));
			if (!token_num)
				return (print_error(SYNTAX_ERROR, "newline"));
		}
		node = node->next;
	}
	return (0);
}
