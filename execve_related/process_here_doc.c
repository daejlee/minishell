#include "minishell.h"
#include "process.h"

static char	*ft_strjoin_modified_x(char const *s1, char const *s2)
{
	int				i;
	unsigned int	s1_len;
	char			*res;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 2));
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\n';
	i = 0;
	while (s2[i])
	{
		res[s1_len + 1 + i] = s2[i];
		i++;
	}
	res[s1_len + 1 + i] = '\0';
	return (res);
}

int	here_doc_seg(t_pcs *p, t_token *now, int i)
{
	char	*limiter;
	int		here_doc_fd;
	int		fst_flag;
	char	*ret;
	char	*temp;
	char	*buf;

	limiter = now->next->origin_str;
	here_doc_fd = open(p->here_doc_buffers[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (here_doc_fd == -1)
		return (1);
	ret = "";
	temp = NULL;
	fst_flag = 1;
	while (1)
	{
		buf = readline(">");
		if (!ft_strncmp(buf, limiter, ft_strlen(buf)))
			break ;
		if (!fst_flag)
		{
			ret = ft_strjoin_modified_x(ret, buf);
			free(buf);
		}
		else
			ret = buf;
		fst_flag = 0;
	}
	free (buf);
	ret = ft_strjoin(ret, "\n");
	write(here_doc_fd, ret, ft_strlen(ret));
	close(here_doc_fd);
	free(ret);
	return (0);
}

static int	get_here_doc_cnt(t_token_meta *meta)
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

int	here_doc(t_token_meta *meta, t_pcs *p)
{
	pid_t	pid;
	t_token	*now;
	int		fst_flag;
	int		i;
	int		status;

	get_here_doc_buffers(meta, p);
	now = meta->head;
	pid = fork();
	if (!pid)
	{
		i = 0;
		fst_flag = 1;
		while (now != meta->head || fst_flag)
		{
			if (now->type == I_HRDOC)
			{
				if (here_doc_seg(p, now, i))
					return (err_terminate(p));
				i++;
			}
			now = now->next;
			fst_flag = 0;
		}
		exit (0);
	}
	else
		waitpid(pid, NULL, 0);
	if (WEXITSTATUS(status) == SIGINT || WEXITSTATUS(status) == SIGQUIT)
	{
		i = get_here_doc_cnt(meta);
		while (i--)
			unlink(p->here_doc_buffers[i]);
	}
	return (WEXITSTATUS(status));
}
