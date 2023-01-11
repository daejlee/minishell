/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fd_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:19:57 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 12:55:37 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void	prep_i(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	if (pcs_cnt == 1)
		prep(p->infile_fd, 1);
	else if (i == pcs_cnt - 1)
		prep(p->infile_fd, p->stdinout_storage[1]);
	else
		prep(p->infile_fd, p->pfd_arr[i][1]);
}

static void	prep_o(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	if (pcs_cnt == 1 || !i)
		prep(0, p->outfile_fd);
	else
		prep(p->pfd_arr[i - 1][0], p->outfile_fd);
}

static void	prep_no_redir(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	if (pcs_cnt == 1)
		return ;
	else if (i == pcs_cnt - 1)
		prep(p->pfd_arr[i - 1][0], p->stdinout_storage[1]);
	else if (!i)
		prep(0, p->pfd_arr[i][1]);
	else
		prep(p->pfd_arr[i - 1][0], p->pfd_arr[i][1]);
}

void	prep_fds(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	int	redir_flag;

	redir_flag = check_redir(p);
	if (redir_flag == I_O_BOTH)
		prep(p->infile_fd, p->outfile_fd);
	else if (redir_flag == I_ONLY)
		prep_i(p, i, pcs_cnt, meta);
	else if (redir_flag == O_ONLY)
		prep_o(p, i, pcs_cnt, meta);
	else
		prep_no_redir(p, i, pcs_cnt, meta);
}
