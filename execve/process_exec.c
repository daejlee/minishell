/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:18:53 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 12:55:34 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

int	exec_fork(t_pcs *p, t_token_meta *meta, t_env *env)
{
	int		i;
	t_token	*now;
	int		stdout_dup;

	if (prep_exec_loop(p, meta))
		return (1);
	stdout_dup = dup(1);
	i = 0;
	now = meta->head;
	while (i < p->pcs_cnt)
	{
		now = prep_redir_n_com(p, meta, now, i);
		if (!now)
			break ;
		signal_execute();
		launch_com(p, now, env, i);
		i++;
		now = now->next;
		signal_ignore();
	}
	return (wrap_up_pcs(p, meta, stdout_dup));
}
