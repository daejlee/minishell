#include "minishell.h"
#include "process.h"

static char	**get_sh_path(t_env *env, int *no_path_flag)
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
		if (!ft_strncmp("PATH", now->key, 4) && now->value)
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
	*no_path_flag = 1;
	return (no_path_flag);
}

static char	*get_sh_func(char **com, t_env *env, int *no_path_flag)
{
	char			*sh_func;
	char			**sh_paths;
	unsigned int	i;

	i = 0;
	sh_paths = get_sh_path(env, no_path_flag);
	if (!sh_paths)
		return (NULL);
	if (*no_path_flag)
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
	sh_func = com[0];
	free_arr(sh_paths);
	return (sh_func);
}

void	exec_com(t_pcs *p, t_token *now, t_env *env)
{
	char	*sh_func;
	int		no_path_flag;

	if (is_built_in(p->com[0]))
	{
		g_exit_status = exec_built_in(p->com, env);
		return ;
	}
	no_path_flag = 0;
	sh_func = get_sh_func(p->com, env, &no_path_flag);
	if (no_path_flag)
	{
		execve_failed(p, p->com[0]);
		return ;
	}
	if (!sh_func)
	{
		free(p->com);
		exit (err_terminate(p));
	}
	execve((const char *)sh_func, (char *const *)p->com, p->envp);
	execve_failed(p, sh_func);
}

int	here_doc_seg(t_pcs *p, t_token *now)
{
	char	*limiter;
	int		here_doc_fd;
	char	*ret;
	char	*temp;
	int		fst_flag;
	char	*buf;

	limiter = now->next->origin_str;
	unlink(HERE_DOC_INPUT_BUFFER);
	here_doc_fd = open(HERE_DOC_INPUT_BUFFER, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (here_doc_fd == -1)
		return (1);
	ret = "";
	fst_flag = 1;
	while (!ft_strnstr(ret, limiter, ft_strlen(ret)))
	{
		buf = readline(">");
		temp = ret;
		ret = ft_strjoin(ret, buf);
		free(buf);
		if (!fst_flag)
			free(temp);
		fst_flag = 0;
	}
	temp = ft_strnstr(ret, limiter, ft_strlen(ret));
	*temp = '\n';
	*(temp + 1) = '\0';
	write(here_doc_fd, ret, ft_strlen(ret));
	close(here_doc_fd);
	here_doc_fd = open(HERE_DOC_INPUT_BUFFER, O_RDONLY);
	p->temp_infile_fd = here_doc_fd;
	free(ret);
	return (0);
}

t_token	*prep_fd_n_move(t_token *now, int i, int pcs_cnt, t_token_meta *meta, t_pcs *p)
{
	if (now == meta->head)
		now = now->next;
	while (now->type != PIPE && now != meta->head)
		now = now->next;
	if (now->type == PIPE && i == pcs_cnt - 1)
		now = now->next;
	prep_fds(p, i, pcs_cnt, meta);
	return (now);
}

char	**get_trimmed_com(t_token *now, t_token_meta *meta)
{
	int		slot_cnt;
	char	**ret;
	t_token	*temp;
	int		i;

	temp = now;
	slot_cnt = 1;
	if (now == meta->head)
	{
		now = now->next;
		slot_cnt++;
	}
	while (now->type != PIPE && now != meta->head)
	{
		if (now->type == ARG)
			slot_cnt++;
		else
			now = now->next;
		now = now->next;
	}
	ret = (char **)malloc(sizeof(char *) * slot_cnt);
	if (!ret)
		return (NULL);
	now = temp;
	i = 0;
	while (i < slot_cnt - 1)
	{
		if (now->type == ARG)
		{
			ret[i] = now->str;
			i++;
		}
		else
			now = now->next;
		now = now->next;
	}
	ret[slot_cnt - 1] = NULL;
	return (ret);
}

char	**get_com(t_token *now, t_token_meta *meta)
{
	char	**ret;

	ret = NULL;
	if (now->type != ARG)
		now = now->next->next;
	else
	{
		ret = get_trimmed_com(now, meta);
		return (ret);
	}
	while (now->type != PIPE && now != meta->head)
	{
		if (now->type != ARG)
			now = now->next->next;
		else
		{
			ret = get_trimmed_com(now, meta);
			return (ret);
		}
	}
	return (ret);
}

int	get_pipes(t_pcs *p, int pcs_cnt)
{
	int	i;

	i = 0;
	while (i < pcs_cnt)
	{
		p->pfd_arr[i] = (int *)malloc(sizeof(int[2]));
		pipe(p->pfd_arr[i]);
		i++;
	}
	return (0);
}

int	exec_fork(t_pcs *p, t_token_meta *meta, t_env *env)
{
	int		i;
	int		pcs_cnt;
	int		ret;
	t_token	*now;
	int		temp_flag;
	int		temp;

	pcs_cnt = get_pcs_cnt(meta);
	p->pids = (pid_t *)malloc(sizeof(pid_t) * (pcs_cnt));
	if (!p->pids)
		return (err_terminate(p));
	p->pfd_arr = (int **)malloc(sizeof (int *) * (pcs_cnt));
	if (!p->pfd_arr)
		return (err_terminate(p));
	if (get_pipes(p, pcs_cnt))
		return (err_terminate(p));
	p->stdinout_storage[0] = dup(0);
	p->stdinout_storage[1] = dup(1);
	temp = dup(1);

	i = 0;
	now = meta->head;
	if (p->infile_fd == -1)
	{
		while (now->type == ARG)
			now = now->next;
		pcs_cnt--;
		while (now->type != PIPE && now != meta->head)
		{
			if (now->type != ARG)
				now = now->next->next;
			else
				break ;
		}
		now = now->next;
	}
	while (i < pcs_cnt)
	{
		temp_flag = 0;
		while (now->type == I_REDIR || now->type == I_HRDOC || now->type == O_REDIR || now->type == O_APPND)
			now = now->next->next;
		if (now->type == EMPTY && now->next != meta->head)
			now = now->next;
		else if (now->type == EMPTY)
		{
			prep_fd_n_move(now, i, pcs_cnt, meta, p);
			break ;
		}
		if (now->type == PIPE)
		{
			now = now->next;
			temp_flag = 1;
		}
		if (p->com)
			free(p->com);
		p->com = get_com(now, meta);
		if (!p->com)
			return (err_terminate(p));
		now = prep_fd_n_move(now, i, pcs_cnt, meta, p);
		if (temp_flag)
		{
			temp_flag = open(EMPTY_BUFFER, O_RDONLY | O_CREAT, 0644);
			if (!temp_flag)
				return (err_terminate(p));
			dup2(temp_flag, 0);
		}
		if (!is_built_in(p->com[0]))
		{
			p->pids[i] = fork();
			if (p->pids[i] == -1)
				return (err_terminate(p));
			else if (!p->pids[i])
			{
				if (i)
					close(p->pfd_arr[i - 1][1]);
				close(p->pfd_arr[i][0]);
				exec_com(p, now, env);
			}
		}
		else
		{
			p->pids[i] = -1;
			exec_com(p, now, env);
		}
		i++;
		now = now->next;
	}
	unlink(HERE_DOC_INPUT_BUFFER);
	unlink(EMPTY_BUFFER);
	i = 0;
	while (i < pcs_cnt)
	{
		close(p->pfd_arr[i][0]);
		close(p->pfd_arr[i][1]);
		i++;
	}
	close(0);
	close(1);
	ret = wait_for_children(p, p->pids, pcs_cnt);
	p->stdinout_storage[1] = temp;
	reset_fds(p, p->stdinout_storage, meta, pcs_cnt);
	if (!pcs_cnt)
		return (g_exit_status);
	else
		return (ret);
}
