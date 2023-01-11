/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:45:54 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 12:55:52 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

t_token	*get_i_redir_location(t_token_meta *meta)
{
	t_token	*now;

	now = meta->head;
	if (now->type == I_REDIR || now->type == I_HRDOC)
		return (now);
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == I_REDIR || now->type == I_HRDOC)
			return (now);
		now = now->next;
	}
	return (now);
}

t_token	*get_o_redir_location(t_token_meta *meta)
{
	t_token	*now;

	now = meta->head;
	if (now->type == O_REDIR || now->type == O_APPND)
		return (now);
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == O_REDIR || now->type == O_APPND)
			return (now);
		now = now->next;
	}
	return (now);
}

static int	get_pcs_cnt_seg(t_token *now, t_token_meta *meta, int ret)
{
	while (now != meta->head)
	{
		if (now->type == ARG)
		{
			ret++;
			now = now->next;
			while (now->type != PIPE && now != meta->head)
			{
				if (now->type == PIPE)
					break ;
				if (now->type >= I_REDIR && now->type <= O_APPND)
					now = now->next->next;
				else if (now->type == ARG && now != meta->head)
					now = now->next;
			}
		}
		else if (now->type >= I_REDIR && now->type <= O_APPND)
			now = now->next->next;
		else
			now = now->next;
	}
	if (meta->head->prev->type == EMPTY)
		ret++;
	return (ret);
}

int	get_pcs_cnt(t_token_meta *meta)
{
	int		ret;
	t_token	*now;

	ret = 0;
	now = meta->head;
	if (now->type == ARG)
	{
		ret++;
		now = now->next;
		while (now->type != PIPE && now != meta->head)
		{
			if (now->type == PIPE)
				break ;
			if (now->type >= I_REDIR && now->type <= O_APPND)
				now = now->next->next;
			else if (now->type == ARG && now != meta->head)
				now = now->next;
		}
	}
	else if (now->type >= I_REDIR && now->type <= O_APPND)
		now = now->next->next;
	else
		now = now->next;
	return (get_pcs_cnt_seg(now, meta, ret));
}
