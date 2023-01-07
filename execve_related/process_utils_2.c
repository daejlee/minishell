#include "minishell.h"
#include "process.h"

int	wait_for_children(t_pcs *p, pid_t *pids, int pcs_cnt)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	waitpid(pids[pcs_cnt - 1], &status, 0);
	while (i < pcs_cnt)
	{
		kill(pids[i], SIGKILL);
		waitpid(pids[i++], NULL, 0);
	}
	free(pids);
	return (WEXITSTATUS(status));
}

int	err_terminate(t_pcs *p)
{
	if (p->infile_fd != -1)
		close(p->infile_fd);
	if (p->outfile_fd != -1)
		close(p->outfile_fd);
	if (p->pfd_arr)
		//free pfdarr;
	if (p->pids)
		free(p->pids);
	close(0);
	close(1);
	if (p->here_doc_flag)
		unlink(HERE_DOC_INPUT_BUFFER);
	unlink(EMPTY_BUFFER);
	return (1);
}

void	execve_failed(t_pcs *p, char *sh_func)
{
	err_terminate(p);
	write(2, "minishell: ", 12);
	write(2, sh_func, ft_strlen(sh_func));
	write(2, ": command not found\n", 21);
	free_arr(p->com);
	if (sh_func)
		free(sh_func);
	exit (127);
}

void	init_p(t_pcs *p)
{
	p->here_doc_flag = 0;
	p->outfile_fd = 1;
	p->infile_fd = 0;
	p->temp_infile_fd = 0;
	p->pfd_arr = NULL;
	p->com = NULL;
	p->envp = NULL;
	p->stdinout_storage[0] = -1;
	p->stdinout_storage[1] = -1;
	p->pids = NULL;
}

int	check_redir(t_token_meta *meta)
{
	t_token	*now;
	int		input_flag;
	int		output_flag;

	input_flag = 0;
	output_flag = 0;
	now = meta->head;
	if (now->type == I_REDIR || now->type == I_HRDOC)
		input_flag = 1;
	if (now->type == O_REDIR || now->type == O_APPND)
		output_flag = 1;
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == I_REDIR || now->type == I_HRDOC)
			input_flag = 1;
		if (now->type == O_REDIR || now->type == O_APPND)
			output_flag = 1;
		now = now->next;
	}
	if (input_flag && output_flag)
		return (I_O_BOTH);
	else if (input_flag)
		return (I_ONLY);
	else if (output_flag)
		return (O_ONLY);
	else
		return (NONE);
}
