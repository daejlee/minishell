#include "../minishell.h"
#include "./process.h"

int	wait_for_children(t_pcs *p, pid_t *pids, int temp)
{
	int	i;
	int	status;

	status = 0;
	close(p->pfd[0]);
	close(p->pfd[1]);
	close(p->next_pfd[0]);
	close(p->next_pfd[1]);
	close(0);
	close(1);
	i = 0;
	while (i < temp)
		waitpid(pids[i++], &status, 0);
	free(pids);
	return (status);
}

int	free_arr(char **com)
{
	unsigned int	i;

	i = 0;
	while (com[i])
		free(com[i++]);
	free(com);
	return (0);
}

int	err_terminate(t_pcs *p)
{
	perror("pipex error");
	if (p->infile_fd != -1)
		close(p->infile_fd);
	if (p->outfile_fd != -1)
		close(p->outfile_fd);
	if (p->pfd)
	{
		close(p->pfd[0]);
		close(p->pfd[1]);
	}
	if (p->next_pfd)
	{
		close(p->next_pfd[0]);
		close(p->next_pfd[1]);
	}
	close(0);
	close(1);
	if (p->here_doc_flag)
		unlink(HERE_DOC_INPUT_BUFFER);
	return (1);
}

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

char	*ft_strjoin_modified(char const *s1, char const *s2)
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
	res[i] = '/';
	i = 0;
	while (s2[i])
	{
		res[s1_len + 1 + i] = s2[i];
		i++;
	}
	res[s1_len + 1 + i] = '\0';
	return (res);
}

static char	**get_sh_path(t_env *env)
{
	unsigned int	i;
	char			**sh_paths;
	t_env			*now;

	i = 0;
	now = env;
	if (!ft_strncmp("PATH", now->key, 4))
	{
		sh_paths = ft_split(now->value, ':');
		if (!sh_paths)
			return (NULL);
		ft_strlcpy(sh_paths[0], sh_paths[0] + 5,
			ft_strlen(sh_paths[0]) - 4);
		return (sh_paths);
	}
	now = now->next;
	while (now != env)
	{
		if (!ft_strncmp("PATH", now->key, 4))
		{
			sh_paths = ft_split(now->value, ':');
			if (!sh_paths)
				return (NULL);
			ft_strlcpy(sh_paths[0], sh_paths[0] + 5,
				ft_strlen(sh_paths[0]) - 4);
			return (sh_paths);
		}
		else
			now = now->next;
	}
	return (NULL);
}

static char	*get_sh_func(char **com, t_env *env)
{
	char			*sh_func;
	char			**sh_paths;
	unsigned int	i;

	i = 0;
	if (!access((const char *)com[0], X_OK))
		return (com[0]);
	sh_paths = get_sh_path(env);
	if (!sh_paths)
		return (NULL);
	while (sh_paths[i])
	{
		sh_func = ft_strjoin_modified(sh_paths[i++], com[0]);
		if (!access(sh_func, X_OK) || !sh_func)
		{
			free_arr(sh_paths);
			return (sh_func);
		}
		free(sh_func);
	}
	sh_func = ft_strjoin_modified(sh_paths[0], com[0]);
	free_arr(sh_paths);
	return (sh_func);
}

void	exec_com(t_pcs *p, t_token *now, int i, t_env *env)
{
	char	*sh_func;

	close(p->next_pfd[0]);
	p->com = ft_split(now->str, ' ');
	if (!p->com)
		exit (err_terminate(p));
	sh_func = get_sh_func(p->com, env);
	if (!sh_func)
	{
		free_arr(p->com);
		exit (err_terminate(p));
	}
	execve((const char *)sh_func, (char *const *)p->com, p->envp);
	execve_failed(p, sh_func);
}

int	exec_fork(t_pcs *p, t_token_meta *meta, t_env *env)
{
	int		i;
	int		ret;
	int		pcs_cnt;
	t_token	*now;

	// here_doc은 나중에
	// if (p->here_doc_flag)
	// {
	// 	ret = here_doc(p, meta);
	// 	if (ret)
	// 		return (ret);
	// 	else
	// 		return (0);
	// }

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
		else //now == ARG
		{
			p->pids[i] = fork();
			if (p->pids[i] == -1)
				return (err_terminate(p));
			else if (p->pids[i])
				exec_com(p, now, i, env);
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
	return (wait_for_children(p, p->pids, pcs_cnt));
}

//	ARG	I_R	ARG		P	ARG				O_R	ARG
//	cat	<	infile	|	grep	"now"	>	outfile
int	get_pcs(t_token_meta *meta, t_env *env, char **envp)
{
	t_pcs	p;
	t_token	*now;

	init_p(&p);
	p.envp = envp;
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
	return (exec_fork(&p, meta, env));
}