/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:45:57 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 15:24:25 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void	free_pfd_arr(int **pfd_arr)
{
	int	i;

	i = 0;
	while (pfd_arr[i])
	{
		free(pfd_arr[i]);
		i++;
	}
	free(pfd_arr);
}

void	err_terminate(t_pcs *p)
{
	if (p->infile_fd != -1)
		close(p->infile_fd);
	if (p->outfile_fd != -1)
		close(p->outfile_fd);
	if (p->pfd_arr)
		free_pfd_arr(p->pfd_arr);
	if (p->pids)
		free(p->pids);
	close(0);
	close(1);
	unlink(EMPTY_BUFFER);
}

int	get_pipes(t_pcs *p, int pcs_cnt)
{
	int	i;

	i = 0;
	while (i < pcs_cnt)
	{
		p->pfd_arr[i] = (int *)malloc(sizeof(int) * 2);
		if (!p->pfd_arr[i])
			return (print_error(MALLOC_FAIL, NULL));
		pipe(p->pfd_arr[i]);
		i++;
	}
	return (0);
}
