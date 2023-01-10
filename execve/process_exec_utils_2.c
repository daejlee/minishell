/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:35:36 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 03:37:14 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "process.h"

static int	get_com_slots(t_token *now, t_token_meta *meta)
{
	int	slot_cnt;

	slot_cnt = 1;
	if (now == meta->head)
	{
		now = now->next;
		slot_cnt++;
	}
	while (now->type != PIPE && now != meta->head)
	{
		if (now->type == ARG)
			slot_cnt++;
		else
			now = now->next;
		now = now->next;
	}
	return (slot_cnt);
}

char	**get_trimmed_com(t_token *now, t_token_meta *meta)
{
	int		slot_cnt;
	char	**ret;
	t_token	*temp;
	int		i;

	slot_cnt = get_com_slots(now, meta);
	ret = (char **)malloc(sizeof(char *) * slot_cnt);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < slot_cnt - 1)
	{
		if (now->type == ARG)
		{
			ret[i] = now->str;
			i++;
		}
		else
			now = now->next;
		now = now->next;
	}
	ret[slot_cnt - 1] = NULL;
	return (ret);
}

char	**get_com(t_token *now, t_token_meta *meta)
{
	char	**ret;

	ret = NULL;
	if (now->type != ARG)
		now = now->next->next;
	else
	{
		ret = get_trimmed_com(now, meta);
		return (ret);
	}
	while (now->type != PIPE && now != meta->head)
	{
		if (now->type != ARG)
			now = now->next->next;
		else
		{
			ret = get_trimmed_com(now, meta);
			return (ret);
		}
	}
	return (ret);
}

int	launch_com(t_pcs *p, t_token *now, t_env *env, int i)
{
	if (!is_built_in(p->com[0]))
	{
		p->pids[i] = fork();
		if (p->pids[i] == -1)
			err_terminate(p);
		else if (!p->pids[i])
		{
			if (i)
				close(p->pfd_arr[i - 1][1]);
			close(p->pfd_arr[i][0]);
			exec_com(p, now, env);
		}
	}
	else
	{
		p->pids[i] = -1;
		exec_com(p, now, env);
	}
	return (0);
}

int	wrap_up_pcs(t_pcs *p, t_token_meta *meta, int stdout_dup)
{
	int	i;
	int	ret;

	unlink(EMPTY_BUFFER);
	i = 0;
	while (i < p->pcs_cnt)
	{
		close(p->pfd_arr[i][0]);
		close(p->pfd_arr[i][1]);
		i++;
	}
	i = get_here_doc_cnt(meta);
	while (i--)
		unlink(p->here_doc_buffers[i]);
	free (p->here_doc_buffers);
	close(0);
	close(1);
	p->stdinout_storage[1] = stdout_dup;
	ret = wait_for_children(p, p->pids, p->pcs_cnt);
	reset_fds(p, p->stdinout_storage, meta, p->pcs_cnt);
	if (!p->pcs_cnt)
		return (g_exit_status);
	else
		return (ret);
}
