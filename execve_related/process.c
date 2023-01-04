#include "../minishell.h"
#include "process.h"

t_token	*get_last_redir(t_token *head)
{
	t_token	*now;
	t_token	*ret;

	now = head;
	if (now->type == I_REDIR || now->type == I_HRDOC)
		ret = now;
	now = now->next;
	while (now != head)
	{
		if (now->type == I_REDIR || now->type == I_HRDOC)
			ret = now;
		now = now->next;
	}
	return (ret);
}

//	ARG	I_R	ARG		I_HD	LIMITER		I_HD	LIMITER		PIPE	ARG		ARG	O_R	ARG			O_R	ARG			O_A	ARG
//	cat	<	infile	<<		limiter0	<<		limiter1	|		grep	a	>	outfile1	>	outfile2	>>	outfile3
int	get_pcs(t_token_meta *meta, t_env *env, char **envp)
{
	t_pcs	p;
	t_token	*now;

	init_p(&p);
	p.envp = envp;
	now = meta->head;
	if (now->type == I_HRDOC)
	{
		if (here_doc_seg(&p, now))
			return (err_terminate(&p));
	}
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == I_HRDOC)
		{
			if (here_doc_seg(&p, now))
				return (err_terminate(&p));
		}
		now = now->next;
	}

	now = meta->head;
	if (now->type == I_REDIR)
		p.infile_fd = open(now->next->str, O_RDONLY);
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == I_REDIR)
		{
			if (p.infile_fd)
				close(p.infile_fd);
			p.infile_fd = open(now->next->str, O_RDONLY);
			if (p.infile_fd == -1)
			{
				write(2, "minishell: ", 12);
				write(2, now->next->str, ft_strlen(now->next->str));
				write(2, ": No such file or directory\n", 29);
				break ;
			}
		}
		now = now->next;
	}
	if (get_last_redir(meta->head) == I_HRDOC)
		p.infile_fd = p.temp_infile_fd;

	now = meta->head;
	if (now->type == O_APPND)
		p.outfile_fd = open(now->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (now->type == O_REDIR)
		p.outfile_fd = open(now->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	now = now->next;
	while (now != meta->head)
	{
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
		now = now->next;
	}
	p.pfd = p.pfd_arr[0];
	p.next_pfd = p.pfd_arr[1];
	return (exec_fork(&p, meta, env));
}
