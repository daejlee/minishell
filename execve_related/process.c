#include "../minishell.h"
#include "./process.h"

void	init_p(t_pcs *p)
{
	p->here_doc_flag = 0;
	p->outfile_fd = 1;
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

static void	prep(int input_fd, int output_fd, int closing_fd, t_pcs *p)
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

void	prep_fds(t_pcs *p, int i, int pcs_cnt)
{
	if (p->here_doc_flag)
	{
		if (!i)
			prep(p->infile_fd, p->next_pfd[1], 0, p);
		else if (i == pcs_cnt - 1)
			prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
	else
	{
		if (!i)
			prep(p->infile_fd, p->next_pfd[1], 0, p);
		else if (i == pcs_cnt - 1)
			prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
}

void	exec_com(t_pcs *p, t_token *now, int i)
{
	char	*sh_func;

	close(p->next_pfd[0]);
	p->com = ft_split(argv[i], ' ');
	if (!p->com)
		exit (err_terminate(p));
	sh_func = get_sh_func(p->com, p->envp);
	if (!sh_func)
	{
		free_arr(p->com);
		exit (err_terminate(p));
	}
	execve((const char *)sh_func, (char *const *)p->com, p->envp);
	execve_failed(p, sh_func);
}

int	exec_fork(t_pcs *p, t_token_meta *meta)
{
	int		i;
	int		ret;
	int		pcs_cnt;
	t_token	*now;

	if (p->here_doc_flag)
	{
		ret = here_doc(p, meta);
		if (ret)
			return (ret);
		else
			return (0);
	}

	pcs_cnt = get_pcs_cnt(meta);
	p->pids = (pid_t *)malloc(sizeof(pid_t) * (pcs_cnt));
	if (!p->pids)
		return (err_terminate(p));
	
	i = 0;
	now = meta->head;

	//리다이렉션과 파이프를 상정하고 분기할 것.
	while (i < pcs_cnt)
	{
		if (now->type == PIPE)
			now = now->next;
		else if (now->type != ARG) //now == I_REDIR
			now = now->next->next;
		else
		{
			p->pids[i] = fork();
			if (p->pids[i] == -1)
				return (err_terminate(p));
			else if (p->pids[i])
				exec_com(p, now, i);
			if (now->next->type == PIPE) //now == ARG && NEXT == PIPE
			{
				if (pipe(p->next_pfd) == -1)
					return (err_terminate(p));
				if (p->infile_fd == -1 && !i) //when infile_fd == -1 and fst loop
					close(p->next_pfd[1]);
				prep_fds(p, i, pcs_cnt);
			}
			swap_pfd(&p->next_pfd, &p->pfd);
			i++;
		}
	}
	return (wait_for_children(p, p->pids, argc - 2));
}

//	ARG	I_R	ARG		P	ARG				O_R	ARG
//	cat	<	infile	|	grep	"now"	>	outfile
int	get_pcs(t_token_meta *meta)
{
	t_pcs	p;
	t_token	*now;

	init_p(&p);
	now = meta->head->next;
	if (now->type == I_REDIR)
		p.infile_fd = open(now->next->str, O_RDONLY);
	else if (now->type == I_HRDOC)
		p.here_doc_flag = 1;
	if (p.infile_fd == -1)
		perror("pipex error");
	now = meta->head->prev->prev;
	if (now->type == O_APPEND)
		p.outfile_fd = open(now->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (now->type == O_REDIR)
		p.outfile_fd = open(now->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (p.outfile_fd == -1)
		return (err_terminate(&p));
	p.pfd = p.pfd_arr[0];
	p.next_pfd = p.pfd_arr[1];
	return (exec_fork(&p, meta));
}
