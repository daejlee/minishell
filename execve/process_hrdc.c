/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hrdc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:35:42 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 14:35:17 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static int	chld_hrdc(t_pcs *p, t_token *now, t_token_meta *meta)
{
	int	fst_flag;
	int	i;

	i = 0;
	fst_flag = 1;
	while (now != meta->head || fst_flag)
	{
		if (now->type == I_HRDOC)
		{
			if (here_doc_seg(p, now, i))
				err_terminate(p);
			i++;
		}
		now = now->next;
		fst_flag = 0;
	}
	exit (0);
}

int	here_doc(t_token_meta *meta, t_pcs *p)
{
	pid_t	pid;
	t_token	*now;
	int		i;
	int		status;

	get_here_doc_buffers(meta, p);
	now = meta->head;
	if (!get_here_doc_cnt(meta))
		return (0);
	pid = fork();
	if (!pid)
	{
		signal_heredoc();
		chld_hrdc(p, now, meta);
	}
	else
		waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == SIGINT || WEXITSTATUS(status) == SIGQUIT)
	{
		i = get_here_doc_cnt(meta);
		while (i--)
			unlink(p->here_doc_buffers[i]);
	}
	return (status);
}
