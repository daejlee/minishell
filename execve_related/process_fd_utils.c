#include "minishell.h"
#include "process.h"

void	swap_pfd(int **pfd1, int **pfd2)
{
	int	*temp;

	temp = *pfd1;
	*pfd1 = *pfd2;
	*pfd2 = temp;
}

static void	prep(int input_fd, int output_fd, int closing_fd, t_pcs *p)
{
	close(closing_fd);
	if (input_fd)
	{
		dup2(input_fd, 0);
		close(input_fd);
	}
	if (output_fd != 1)
	{
		dup2(output_fd, 1);
		close(output_fd);
	}
}

void	prep_fds(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta, int stdinout_storage[2])
{
	int	redir_flag;

	redir_flag = check_redir(meta);
	// if (redir_flag == I_O_BOTH)
	// {
	// 	if (pcs_cnt == 1)
	// 		prep(p->infile_fd, p->outfile_fd, -1, p);
	// 	else if (i == pcs_cnt - 1)
	// 		prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
	// 	else if (!i)
	// 		prep(p->infile_fd, p->next_pfd[1], 0, p);
	// 	else
	// 		prep(p->pfd[0], p->next_pfd[1], p->pfd[1], p);
	// }
	// else if (redir_flag == I_ONLY)
	// {
	// 	if (pcs_cnt == 1)
	// 		prep(p->infile_fd, 1, -1, p);
	// 	else if (i == pcs_cnt - 1)
	// 		prep(p->pfd[0], stdinout_storage[1], 0, NULL);
	// 	else if (!i)
	// 		prep(p->infile_fd, p->next_pfd[1], 0, p);
	// 	else
	// 		prep(p->pfd[0], p->next_pfd[1], p->pfd[1], p);
	// }
	// else if (redir_flag == O_ONLY)
	// {
	// 	if (pcs_cnt == 1)
	// 		prep(0, p->outfile_fd, -1, p);
	// 	else if (i == pcs_cnt - 1)
	// 		prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
	// 	else if (!i)
	// 		prep(0, p->next_pfd[1], 1, p);
	// 	else
	// 		prep(p->pfd[0], p->next_pfd[1], p->pfd[1], p);
	// }
	{
		if (pcs_cnt == 1)
			return ;
		else if (i == pcs_cnt - 1)
			prep(p->pfd_arr[i - 1][0], stdinout_storage[1], -1, NULL);
		else if (!i)
			prep(0, p->pfd_arr[i][1], 1, p); 
		else
			prep(p->pfd_arr[i - 1][0], p->pfd_arr[i][1], -1, p);
	}
}

void	reset_fds(t_pcs *p, int stdin_dup, int stdout_dup, t_token_meta *meta, int pcs_cnt)
{
	int	i;

	i = 0;
	while (i < pcs_cnt)
	{
		close(p->pfd_arr[i][0]);
		close(p->pfd_arr[i][1]);
		i++;
	}
	dup2(stdout_dup, 1);
	dup2(stdin_dup, 0);
	close(stdout_dup);
	close(stdin_dup);
}
