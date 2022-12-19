#include "../minishell.h"
#include "./process.h"

enum	e_redir_flag
{
	I_ONLY,
	O_ONLY,
	I_O_BOTH,
	NONE
};

int	get_pcs_cnt(t_token_meta *meta)
{
	int		ret;
	t_token	*now;

	ret = 0;
	now = meta->head;
	if (now->type == ARG)
		ret++;
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == I_REDIR || now->type == O_REDIR
			|| now->type == I_HRDOC || now->type == O_APPEND)
			now = now->next;
		else if (now->type == ARG)
			ret++;
		now = now->next;
	}
	return (ret);
}

t_token	*get_i_redir_location(t_token_meta *meta)
{
	t_token	*now;

	now = meta->head;
	if (now->type == I_REDIR || now->type == I_HRDOC)
		return (now);
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == I_REDIR || now->type == I_HRDOC)
			return (now);
		now = now->next;
	}
	return (now);
}

t_token	*get_o_redir_location(t_token_meta *meta)
{
	t_token	*now;

	now = meta->head;
	if (now->type == O_REDIR || now->type == O_APPND)
		return (now);
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == O_REDIR || now->type == O_APPND)
			return (now);
		now = now->next;
	}
	return (now);
}

void	swap_pfd(int **pfd1, int **pfd2)
{
	int	*temp;

	temp = *pfd1;
	*pfd1 = *pfd2;
	*pfd2 = temp;
}

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

void	execve_failed(t_pcs *p, char *sh_func)
{
	err_terminate(p);
	free(p->pids);
	free_arr(p->com);
	if (sh_func)
		free(sh_func);
	free(p);
	exit (0);
}

void	init_p(t_pcs *p)
{
	p->here_doc_flag = 0;
	p->outfile_fd = 1;
	p->infile_fd = 0;
	p->pfd_arr[0][0] = 0;
	p->pfd_arr[0][1] = 0;
	p->pfd_arr[1][0] = 0;
	p->pfd_arr[1][1] = 0;
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

int	check_redir(t_token_meta *meta)
{
	t_token	*now;
	int		input_flag;
	int		output_flag;

	input_flag = 0;
	output_flag = 0;
	now = meta->head->next;
	if (now->type == I_REDIR || now->type == I_HRDOC)
		input_flag = 1;
	now = meta->head->prev->prev;
	if (now->type == O_REDIR || now->type == O_APPND)
		output_flag = 1;
	if (input_flag && output_flag)
		return (I_O_BOTH);
	else if (input_flag)
		return (I_ONLY);
	else if (output_flag)
		return (O_ONLY);
	else
		return (NONE);
}

void	prep_fds(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta, int stdinout_storage[2])
{
	int	redir_flag;

	redir_flag = check_redir(meta);
	if (redir_flag == I_O_BOTH)
	{
		if (!i)
			prep(p->infile_fd, p->next_pfd[1], 0, p);
		else if (i == pcs_cnt - 1)
			prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
	else if (redir_flag == I_ONLY)
	{
		if (!i)
			prep(p->infile_fd, p->next_pfd[1], 0, p);
		else if (i == pcs_cnt - 1)
			prep(p->pfd[0], 1, -1, NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
	else if (redir_flag == O_ONLY)
	{
		if (!i)
			prep(0, p->next_pfd[1], -1, p);
		else if (i == pcs_cnt - 1)
			prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
	else
	{
		if (!i)
			prep(0, p->next_pfd[1], 1, p); 
		else if (i == pcs_cnt - 1)
		{
			prep(p->pfd[0], stdinout_storage[1], 0, p);
		}
		else
			prep(p->pfd[0], p->next_pfd[1], p->pfd[1], p);
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

	if (now->next->type == PIPE)
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
	int		stdinout_storage[2];
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

	stdinout_storage[0] = dup(0); //stdin save. 3
	stdinout_storage[1] = dup(1); //stdout save. 4
	while (i < pcs_cnt)
	{
		if (now->type == PIPE && i == pcs_cnt - 1)
		{
			prep_fds(p, i, pcs_cnt, meta, stdinout_storage);
			now = now->next;
		}
		else if (now->type == PIPE)
			now = now->next;
		else if (now->type != ARG) //now == I_REDIR
			now = now->next->next;
		else //now == ARG
		{
			if (now->next->type == PIPE) //NEXT == PIPE
			{
				if (pipe(p->next_pfd) == -1)
					return (err_terminate(p));
				if (p->infile_fd == -1 && !i) // infile_fd == -1 in fst loop
					close(p->next_pfd[1]);
				prep_fds(p, i, pcs_cnt, meta, stdinout_storage);
			}
			p->pids[i] = fork();
			if (p->pids[i] == -1)
				return (err_terminate(p));
			else if (!p->pids[i])
				exec_com(p, now, i, env);
			swap_pfd(&p->next_pfd, &p->pfd);
			i++;
			now = now->next;
		}
	}
	return (wait_for_children(p, p->pids, pcs_cnt));
}

//	ARG	I_R	ARG		P	ARG		ARG		O_R	ARG
//	cat	<	infile	|	grep	"now"	>	outfile
int	get_pcs(t_token_meta *meta, t_env *env, char **envp)
{
	t_pcs	p;
	t_token	*now;

	init_p(&p);
	p.envp = envp;
	now = get_i_redir_location(meta); //재지향 토큰 순서는 2번째가 아닐 수 있다.
	if (now->type == I_REDIR)
		p.infile_fd = open(now->next->str, O_RDONLY);
	else if (now->type == I_HRDOC)
		p.here_doc_flag = 1;
	if (p.infile_fd == -1)
		perror("pipex error");
	now = get_o_redir_location(meta);
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
