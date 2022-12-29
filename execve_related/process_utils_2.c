#include "../minishell.h"
#include "process.h"

int	wait_for_children(t_pcs *p, pid_t *pids, int pcs_cnt)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < pcs_cnt)
		waitpid(pids[i++], &status, 0);
	free(pids);
	return (WEXITSTATUS(status));
}

int	err_terminate(t_pcs *p)
{
	perror("minishell error");
	if (p->infile_fd != -1)
		close(p->infile_fd);
	if (p->outfile_fd != -1)
		close(p->outfile_fd);
	if (p->pfd)
	{
		close(p->pfd[0]);
		close(p->pfd[1]);
	}
	if (p->next_pfd)
	{
		close(p->next_pfd[0]);
		close(p->next_pfd[1]);
	}
	close(0);
	close(1);
	if (p->here_doc_flag)
		unlink(HERE_DOC_INPUT_BUFFER);
	return (1);
}

void	execve_failed(t_pcs *p, char *sh_func)
{
	err_terminate(p);
	free(p->pids);
	free_arr(p->com);
	if (sh_func)
		free(sh_func);
	free(p);
	exit (127);
}

void	init_p(t_pcs *p)
{
	p->here_doc_flag = 0;
	p->outfile_fd = 1;
	p->infile_fd = 0;
	p->pfd_arr[0][0] = 0;
	p->pfd_arr[0][1] = 0;
	p->pfd_arr[1][0] = 0;
	p->pfd_arr[1][1] = 0;
	p->pfd = NULL;
	p->next_pfd = NULL;
	p->com = NULL;
}

int	check_redir(t_token_meta *meta)
{
	t_token	*now;
	int		input_flag;
	int		output_flag;

	input_flag = 0;
	output_flag = 0;
	now = meta->head->next;
	if (now->type == I_REDIR || now->type == I_HRDOC)
		input_flag = 1;
	now = meta->head->prev->prev;
	if (now->type == O_REDIR || now->type == O_APPND)
		output_flag = 1;
	if (input_flag && output_flag)
		return (I_O_BOTH);
	else if (input_flag)
		return (I_ONLY);
	else if (output_flag)
		return (O_ONLY);
	else
		return (NONE);
}
