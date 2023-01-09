#include "minishell.h"
#include "process.h"

int	input_redir(t_token_meta *meta, t_token *now, t_pcs *p, int i)
{
	if (now->type == I_REDIR)
		p->infile_fd = open(now->next->str, O_RDONLY);
	now = now->next;
	while (now != meta->head && now->type != PIPE)
	{
		if (now->type == I_REDIR)
		{
			if (p->infile_fd)
				close(p->infile_fd);
			p->infile_fd = open(now->next->str, O_RDONLY);
			if (p->infile_fd == -1)
			{
				write(2, "minishell: ", 12);
				write(2, now->next->str, ft_strlen(now->next->str));
				write(2, ": No such file or directory\n", 29);
				break ;
			}
		}
		else if (now->type == I_HRDOC)
		{
			if (p->infile_fd)
				close(p->infile_fd);
			p->infile_fd = open(p->here_doc_buffers[i++], O_RDONLY);
		}
		now = now->next;
	}
	return (i);
}

void	output_redir(t_token_meta *meta, t_token *now, t_pcs *p)
{
	int	fst_flag;

	fst_flag = 1;
	while ((now != meta->head && now->type != PIPE) || fst_flag)
	{
		fst_flag = 0;
		if (now->type == O_APPND)
		{
			if (p->outfile_fd != 1)
				close(p->outfile_fd);
			p->outfile_fd = open(now->next->str, O_WRONLY | O_APPEND
					| O_CREAT, 0644);
		}
		else if (now->type == O_REDIR)
		{
			if (p->outfile_fd != 1)
				close(p->outfile_fd);
			p->outfile_fd = open(now->next->str, O_WRONLY | O_TRUNC
					| O_CREAT, 0644);
		}
		now = now->next;
	}
}
