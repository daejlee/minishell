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

static void	prep_i_o(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	if (pcs_cnt == 1)
		prep(p->infile_fd, p->outfile_fd, -1, p);
	else if (i == pcs_cnt - 1)
		prep(p->infile_fd, p->outfile_fd, p->pfd_arr[i - 1][0], NULL);
	else if (!i)
		prep(p->infile_fd, p->outfile_fd, p->pfd_arr[i - 1][0], p);
	else
		prep(p->infile_fd, p->outfile_fd, p->pfd_arr[i - 1][0], p);
}

static void	prep_i(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	if (pcs_cnt == 1)
		prep(p->infile_fd, 1, -1, p);
	else if (i == pcs_cnt - 1)
		prep(p->infile_fd, p->stdinout_storage[1], p->pfd_arr[i - 1][0], NULL);
	else if (!i)
		prep(p->infile_fd, p->pfd_arr[i][1], 0, p);
	else
		prep(p->infile_fd, p->pfd_arr[i][1], p->pfd_arr[i - 1][0], p);
}

static void	prep_o(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	if (pcs_cnt == 1)
		prep(0, p->outfile_fd, -1, p);
	else if (i == pcs_cnt - 1)
		prep(p->pfd_arr[i - 1][0], p->outfile_fd, p->pfd_arr[i - 1][1],
			NULL);
	else if (!i)
		prep(0, p->outfile_fd, 1, p);
	else
		prep(p->pfd_arr[i - 1][0], p->outfile_fd, p->pfd_arr[i - 1][1], p);
}

static void	prep_no_redir(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	if (pcs_cnt == 1)
		return ;
	else if (i == pcs_cnt - 1)
		prep(p->pfd_arr[i - 1][0], p->stdinout_storage[1], -1, NULL);
	else if (!i)
		prep(0, p->pfd_arr[i][1], 1, p);
	else
		prep(p->pfd_arr[i - 1][0], p->pfd_arr[i][1], -1, p);
}

void	prep_fds(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta)
{
	int	redir_flag;

	redir_flag = check_redir(p);
	if (redir_flag == I_O_BOTH)
		prep_i_o(p, i, pcs_cnt, meta);
	else if (redir_flag == I_ONLY)
		prep_i(p, i, pcs_cnt, meta);
	else if (redir_flag == O_ONLY)
		prep_o(p, i, pcs_cnt, meta);
	else
		prep_no_redir(p, i, pcs_cnt, meta);
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
		i++;
	}
	dup2(stdinout_storage[1], 1);
	dup2(stdinout_storage[0], 0);
	close(stdinout_storage[1]);
	close(stdinout_storage[0]);
}
