/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:25:18 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 17:48:27 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void	seg(t_pcs *p, char *str)
{
	if (p->infile_fd)
		close(p->infile_fd);
	p->infile_fd = open(str, O_RDONLY);
}

static void	print_redir_err(t_token *now)
{
	write(2, "minishell: ", 12);
	write(2, now->next->str, ft_strlen(now->next->str));
	perror(" \b");
}

int	input_redir(t_token_meta *meta, t_token *now, t_pcs *p, int i)
{
	int	fst_flag;

	fst_flag = 1;
	p->infile_fd = 0;
	while ((now != meta->head && now->type != PIPE) || fst_flag)
	{
		fst_flag = 0;
		if (now->type == I_REDIR)
		{
			seg(p, now->next->str);
			if (p->infile_fd == -1)
			{
				print_redir_err(now);
				break ;
			}
		}
		else if (now->type == I_HRDOC)
		{
			seg(p, p->here_doc_buffers[i]);
			i++;
		}
		now = now->next;
	}
	return (i);
}

static void	output_redir_seg(t_token *now, t_pcs *p)
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
}

void	output_redir(t_token_meta *meta, t_token *now, t_pcs *p)
{
	int	fst_flag;

	fst_flag = 1;
	p->prev_outfile_fd = p->outfile_fd;
	p->outfile_fd = 1;
	while ((now != meta->head && now->type != PIPE) || fst_flag)
	{
		fst_flag = 0;
		output_redir_seg(now, p);
		if (p->outfile_fd == -1)
		{
			print_redir_err(now);
			break ;
		}
		now = now->next;
	}
}
