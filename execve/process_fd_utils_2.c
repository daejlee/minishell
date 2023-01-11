/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fd_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:20:30 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 11:36:41 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "process.h"

void	swap_pfd(int **pfd1, int **pfd2)
{
	int	*temp;

	temp = *pfd1;
	*pfd1 = *pfd2;
	*pfd2 = temp;
}

void	prep(int input_fd, int output_fd)
{
	if (input_fd)
	{
		close (0);
		dup2(input_fd, 0);
		close(input_fd);
	}
	if (output_fd != 1)
	{
		close (1);
		dup2(output_fd, 1);
		close(output_fd);
	}
}

void	reset_fds(t_pcs *p, int stdinout_storage[2], t_token_meta *meta,
	int pcs_cnt)
{
	int	i;

	i = 0;
	while (i < pcs_cnt)
	{
		close(p->pfd_arr[i][0]);
		close(p->pfd_arr[i][1]);
		free(p->pfd_arr[i]);
		i++;
	}
	dup2(stdinout_storage[1], 1);
	dup2(stdinout_storage[0], 0);
	close(stdinout_storage[1]);
	close(stdinout_storage[0]);
	free(p->pfd_arr);
	free(p->com);
}
