#include "../minishell.h"

typedef struct s_pcs
{
	int		here_doc_flag;
	int		outfile_fd;
	int		infile_fd;
	int		pfd_arr[2][2];
	int		*pfd;
	int		*next_pfd;
	char	**envp;
	char	**com;
	pid_t	*pids;
}	t_pcs;

/* 환경변수 포인터를 받아와 실행 경로를 추출하는 함수입니다. */
char	**get_sh_path(char **envp)
{
	unsigned int	i;
	char			**sh_paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			sh_paths = ft_split(envp[i], ':');
			if (!sh_paths)
				return (NULL);
			ft_strlcpy(sh_paths[0], sh_paths[0] + 5,
				ft_strlen(sh_paths[0]) - 4);
			return (sh_paths);
		}
		else
			i++;
	}
	return (NULL);
}

void	init_p(t_pcs *p)
{
	p->here_doc_flag = 0;
	p->outfile_fd = 0;
	p->infile_fd = 0;
	p->pfd[0] = 0;
	p->pfd[1] = 0;
	(p->pfd + 1)[0] = 0;
	(p->pfd + 1)[1] = 0;
	p->pfd = NULL;
	p->next_pfd = NULL;
	p->envp = NULL;
	p->com = NULL;
}

int	get_child_count(t_token_meta *meta)
{
	int		ret;
	t_token	*now;

	ret = 0;
	now = meta->head;
	if (now->type == CMD)
		ret++;
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == CMD)
			ret++;
		now = now->next;
	}
	return (ret);
}

void	swap_pfd(int **pfd1, int **pfd2)
{
	int	*temp;

	temp = *pfd1;
	*pfd1 = *pfd2;
	*pfd2 = temp;
}

static void	prep(int input_fd, int output_fd, int closing_fd, t_pipex *p)
{
	close(closing_fd);
	if (input_fd)
	{
		dup2(input_fd, 0);
		close(input_fd);
		if (p)
			p->pfd[0] = 0;
	}
	if (output_fd != 1)
	{
		dup2(output_fd, 1);
		close(output_fd);
		if (p)
			p->next_pfd[1] = 1;
	}
}

void	prep_fds(t_pipex *p, int i, int argc)
{
	if (p->here_doc_flag)
	{
		if (i == 3)
			prep(p->infile_fd, p->next_pfd[1], 0, p);
		else if (i == argc - 2)
			prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
	else
	{
		if (i == 2)
			prep(p->infile_fd, p->next_pfd[1], 0, p);
		else if (i == argc - 2)
			prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
}

int	exec_fork(t_pcs *p, t_token_meta *meta, int chld_cnt)
{
	int	i;
	int	ret;

	if (p->here_doc_flag)
	{
		ret = here_doc(p, meta);
		if (ret)
			return (ret);
		else
			return (0);
	}
	p->pids = (pid_t *)malloc(sizeof(pid_t) * (chld_cnt));
	if (!p->pids)
		return (err_terminate(p));
	i = 1;
	while (i++ < chld_cnt + 1)
	{
		if (pipe(p->next_pfd) == -1)
			return (err_terminate(p));
		if (p->infile_fd == -1 && i == 2)
			close(p->next_pfd[1]);
		else
		{
			prep_fds(p, i, argc);
			p->pids[i - 2] = fork();
			if (p->pids[i - 2] == -1)
				return (err_terminate(p));
			else if (!p->pids[i - 2])
				exec_sh(p, argv, i);
		}
		swap_pfd(&p->next_pfd, &p->pfd);
	}
	return (wait_for_children(p, p->pids, argc - 2));
}

/* 실행부 */
int get_process(t_token_meta *meta)
{
	int		chld_cnt;
	t_token	*now;
	t_pcs	p;

	chld_cnt = get_child_count(meta);
	init_p(&p);
	now = meta->head;
	now = now->next;
	if (now->type == I_HRDOC)
		p.here_doc_flag = 1;
	else if (now->type == I_REDIR)
	{
		p.infile_fd = open(now->next->str, O_RDONLY);
		if (p.infile_fd == -1)
			perror("minishell error");
	}
	now = meta->head->prev->prev;
	if (now->type == O_REDIR)
	{
		p.outfile_fd = open(now->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (p.outfile_fd == -1)
			perror("minishell error");
	}
	else if (now->type == O_APPND)
	{
		p.outfile_fd = open(now->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (p.outfile_fd == -1)
			perror("minishell error");
	}
	p.pfd = p.pfd_arr[0];
	p.next_pfd = p.pfd_arr[1];
	return (exec_fork(&p, meta, chld_cnt))
}
