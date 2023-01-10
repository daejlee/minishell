#include "minishell.h"
#include "process.h"

int	err_terminate(t_pcs *p)
{
	if (p->infile_fd != -1)
		close(p->infile_fd);
	if (p->outfile_fd != -1)
		close(p->outfile_fd);
	if (p->pfd_arr)
		free (p->pfd_arr); //1차원 프리도 필요함.
	if (p->pids)
		free(p->pids);
	close(0);
	close(1);
	unlink(EMPTY_BUFFER);
	return (1);
}

int	get_pipes(t_pcs *p, int pcs_cnt)
{
	int	i;

	i = 0;
	while (i < pcs_cnt)
	{
		p->pfd_arr[i] = (int *)malloc(sizeof(int[2]));
		pipe(p->pfd_arr[i]);
		i++;
	}
	return (0);
}
