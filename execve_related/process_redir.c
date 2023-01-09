#include "minishell.h"
#include "process.h"

static t_token	*get_last_redir(t_token *head)
{
	t_token	*now;
	t_token	*ret;

	ret = NULL;
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

int	here_doc(t_token_meta *meta, t_pcs *p)
{
	t_token	*now;

	now = meta->head;
	if (now->type == I_HRDOC)
	{
		if (here_doc_seg(p, now))
			return (err_terminate(p));
	}
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == I_HRDOC)
		{
			if (here_doc_seg(p, now))
				return (err_terminate(p));
		}
		now = now->next;
	}
	return (0);
}

void	input_redir(t_token_meta *meta, t_pcs *p)
{
	t_token	*now;

	now = meta->head;
	if (now->type == I_REDIR)
		p->infile_fd = open(now->next->str, O_RDONLY);
	now = now->next;
	while (now != meta->head)
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
		now = now->next;
	}
	if (get_last_redir(meta->head) && get_last_redir(meta->head)->type == I_HRDOC)
		p->infile_fd = p->temp_infile_fd;
}

static int	output_redir_seg(t_token_meta *meta, t_pcs *p, t_token *now)
{
	now = now->next;
	while (now != meta->head)
	{
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
		if (p->outfile_fd == -1)
			return (err_terminate(&p));
		now = now->next;
	}
	return (0);
}

int	output_redir(t_token_meta *meta, t_pcs *p)
{
	t_token	*now;
	int		ret;

	now = meta->head;
	if (now->type == O_APPND)
		p->outfile_fd = open(now->next->str, O_WRONLY | O_APPEND
				| O_CREAT, 0644);
	else if (now->type == O_REDIR)
			p->outfile_fd = open(now->next->str, O_WRONLY | O_TRUNC
				| O_CREAT, 0644);
	ret = output_redir_seg(meta, p, now);
	if (ret)
		return (ret);
	else
		return (0);
}
