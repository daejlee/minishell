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
	p->outfile_fd = -1;
	p->infile_fd = -1;
	p->pfd_arr = NULL;
	p->com = NULL;
	p->envp = NULL;
	p->stdinout_storage[0] = -1;
	p->stdinout_storage[1] = -1;
	p->pids = NULL;
}

int	check_redir(t_pcs *p)
{
	int		input_flag;
	int		output_flag;

	input_flag = 0;
	output_flag = 0;
	if (p->infile_fd != 0)
		input_flag = p->infile_fd;
	if (p->outfile_fd != 1)
		output_flag = p->outfile_fd;
	if (input_flag && output_flag)
		return (I_O_BOTH);
	else if (input_flag)
		return (I_ONLY);
	else if (output_flag)
		return (O_ONLY);
	else
		return (NONE);
}
