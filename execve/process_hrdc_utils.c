/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hrdc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:14:42 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 12:34:17 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "process.h"

static int	hrdc_seg_seg_1(t_pcs *p, t_hrdc_seg *l, t_token *now, int i)
{
	signal_heredoc();
	l->limiter = now->next->origin_str;
	l->here_doc_fd = open(p->here_doc_buffers[i], O_WRONLY | O_TRUNC
			| O_CREAT, 0644);
	if (l->here_doc_fd == -1)
		return (1);
	l->ret = ft_strdup("");
	l->temp = NULL;
	l->fst_flag = 1;
	return (0);
}

static void	hrdc_seg_seg_2(t_hrdc_seg *l)
{
	char	*temp;

	while (1)
	{
		l->buf = readline(">");
		if (!l->buf)
			break ;
		if (ft_strlen(l->buf) == ft_strlen(l->limiter)
			&& !ft_strncmp(l->buf, l->limiter, ft_strlen(l->limiter)))
			break ;
		temp = l->ret;
		if (!l->fst_flag)
		{
			l->ret = ft_strjoin_modified(l->ret, l->buf, '\n');
			free(l->buf);
		}
		else
			l->ret = ft_strdup(l->buf);
		free(temp);
		l->fst_flag = 0;
	}
	if (l->buf)
		free (l->buf);
}

int	here_doc_seg(t_pcs *p, t_token *now, int i)
{
	t_hrdc_seg	l;

	l.ret = NULL;
	if (hrdc_seg_seg_1(p, &l, now, i))
		return (1);
	hrdc_seg_seg_2(&l);
	l.temp = l.ret;
	l.ret = ft_strjoin(l.ret, "\n");
	if (l.temp)
		free(l.temp);
	write(l.here_doc_fd, l.ret, ft_strlen(l.ret));
	close(l.here_doc_fd);
	free(l.ret);
	signal_default();
	return (0);
}

int	get_here_doc_cnt(t_token_meta *meta)
{
	int		fst_flag;
	t_token	*now;
	int		ret;

	now = meta->head;
	fst_flag = 1;
	ret = 0;
	while (now != meta->head || fst_flag)
	{
		if (now->type == I_HRDOC)
			ret++;
		now = now->next;
		fst_flag = 0;
	}
	return (ret);
}

void	get_here_doc_buffers(t_token_meta *meta, t_pcs *p)
{
	t_token	*now;
	int		i;
	int		here_doc_cnt;
	char	*here_doc_idx;

	now = meta->head;
	here_doc_cnt = get_here_doc_cnt(meta);
	p->here_doc_buffers = (char **)malloc(sizeof(char *) * here_doc_cnt);
	i = 0;
	while (i < here_doc_cnt)
	{
		here_doc_idx = ft_strdup("HERE_DOC_BUFFER__");
		here_doc_idx[16] = i + 48;
		p->here_doc_buffers[i] = here_doc_idx;
		i++;
	}
}
