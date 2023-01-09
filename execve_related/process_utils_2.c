#include "minishell.h"
#include "process.h"

int	wait_for_children(t_pcs *p, pid_t *pids, int pcs_cnt)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < pcs_cnt)
		waitpid(pids[i++], NULL, 0);
	free(pids);
	return (WEXITSTATUS(status));
}

void	execve_failed(t_pcs *p, char *sh_func)
{
	err_terminate(p);
	if (!access(sh_func, F_OK))
	{
		write(2, "minishell: ", 12);
		write(2, sh_func, ft_strlen(sh_func));
		write(2, ": Permission denied\n", 21);
	}
	else
	{
		write(2, "minishell: ", 12);
		write(2, sh_func, ft_strlen(sh_func));
		write(2, ": command not found\n", 21);
	}
	free(p->com);
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

static int	check_redir_seg(int input_flag, int output_flag)
{
	if (input_flag && output_flag)
		return (I_O_BOTH);
	else if (input_flag)
		return (I_ONLY);
	else if (output_flag)
		return (O_ONLY);
	else
		return (NONE);
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
	return (check_redir_seg(input_flag, output_flag));
}
