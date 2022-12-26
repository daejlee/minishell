#include "../minishell.h"
#include "process.h"

//	ARG	I_R	ARG		I_HD	LIMITER		I_HD	LIMITER		PIPE	ARG		ARG	O_R	ARG			O_R	ARG			O_A	ARG
//	cat	<	infile	<<		limiter0	<<		limiter1	|		grep	a	>	outfile1	>	outfile2	>>	outfile3
int	get_pcs(t_token_meta *meta, t_env *env, char **envp)
{
	t_pcs	p;
	t_token	*now;
	t_token	*i_last;

	init_p(&p);
	p.envp = envp;
	now = get_i_redir_location(meta); //재지향 토큰 순서는 2번째가 아닐 수 있다.
	while (now->type == I_REDIR || now->type == I_HRDOC)
	{
		if (now->type == I_HRDOC)
			here_doc_seg(&p, now);
		now = now->next->next;
	}
	i_last = now->prev->prev;

	now = get_i_redir_location(meta);
	while (now->type == I_REDIR || now->type == I_HRDOC)
	{
		if (now->type == I_REDIR)
		{
			if (p.infile_fd)
				close(p.infile_fd);
			p.infile_fd = open(now->next->str, O_RDONLY);
		}
		if (p.infile_fd == -1)
		{
			perror("pipex error");
			break ;
		}
		now = now->next->next;
	}
	if (i_last->type == I_HRDOC)
		p.infile_fd = p.temp_infile_fd;

	now = get_o_redir_location(meta);
	while (now->type == O_REDIR || now->type == O_APPND)
	{
		if (p.outfile_fd != 1)
			close(p.outfile_fd);
		if (now->type == O_APPND)
		{
			if (p.outfile_fd != 1)
				close(p.outfile_fd);
			p.outfile_fd = open(now->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		else if (now->type == O_REDIR)
		{
			if (p.outfile_fd != 1)
				close(p.outfile_fd);
			p.outfile_fd = open(now->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		if (p.outfile_fd == -1)
			return (err_terminate(&p));
		now = now->next->next;
	}
	p.pfd = p.pfd_arr[0];
	p.next_pfd = p.pfd_arr[1];
	return (exec_fork(&p, meta, env));
}
