/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:57:10 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 03:23:59 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "process.h"

t_token	*prep_bad_infile(t_pcs *p, t_token *now, t_token_meta *meta,
		int *temp_flag_adr)
{
	while (now->type == ARG)
		now = now->next;
	p->pcs_cnt--;
	while (now->type != PIPE && now != meta->head)
	{
		if (now->type != ARG)
			now = now->next->next;
		else
			break ;
	}
	now = now->next;
	*temp_flag_adr = 1;
	return (now);
}

t_token	*fast_forward_node(t_pcs *p, t_token *now, t_token_meta *meta,
		int i)
{
	while (now->type == I_REDIR || now->type == I_HRDOC
		|| now->type == O_REDIR || now->type == O_APPND)
		now = now->next->next;
	if (now->type == EMPTY && now->next != meta->head)
		now = now->next;
	else if (now->type == EMPTY)
	{
		prep_fd_n_move(now, i, meta, p);
		return (NULL);
	}
	if (now->type == PIPE)
	{
		now = now->next;
		p->empty_buf_flag = 1;
	}
	return (now);
}

t_token	*prep_redir_n_com(t_pcs *p, t_token_meta *meta, t_token *now,
		int i)
{
	p->hdb_idx = input_redir(meta, now, p, p->hdb_idx);
	output_redir(meta, now, p);
	p->empty_buf_flag = 0;
	if (p->infile_fd == -1)
		now = prep_bad_infile(p, now, meta, &(p->empty_buf_flag));
	now = fast_forward_node(p, now, meta, i);
	if (!now)
		return (NULL);
	if (p->com)
		free(p->com);
	p->com = get_com(now, meta);
	if (!p->com)
		err_terminate(p);
	now = prep_fd_n_move(now, i, meta, p);
	if (p->empty_buf_flag || p->prev_outfile_fd != 1)
	{
		p->empty_buf_flag = open(EMPTY_BUFFER, O_RDONLY | O_CREAT, 0644);
		if (!p->empty_buf_flag)
			err_terminate(p);
		close (0);
		dup2(p->empty_buf_flag, 0);
	}
	return (now);
}
