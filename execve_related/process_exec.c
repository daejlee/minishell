#include "../minishell.h"
#include "process.h"

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

// cat << LIMITER 

static int	here_doc_seg(t_pcs *p, t_token_meta *meta)
{
	t_token	*now;
	char	*limiter;
	int		here_doc_fd;
	char	*ret;
	char	*temp;
	int		fst_flag;
	char	buffer[10];
	char	*prev_nl;

	now = meta->head->next->next;
	limiter = ft_strjoin(now->str, "\n");
	here_doc_fd = open(HERE_DOC_INPUT_BUFFER, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (here_doc_fd == -1)
		return (1);
	ret = "";
	prev_nl = NULL;
	fst_flag = 1;
	while (!ft_strnstr(ret, limiter, ft_strlen(ret)))
	{
		write(1, ">", 1);
		while (1)
		{
			read(0, buffer, 10);
			temp = ret;
			ret = ft_strjoin(ret, buffer);
			if (!fst_flag)
				free(temp);
			if (ft_strrchr(ret, '\n') && ft_strrchr(ret, '\n') != prev_nl)
			{
				*(ft_strrchr(ret, '\n') + 1) = '\0';
				prev_nl = ft_strchr(ret, '\n');
				break ;
			}
			fst_flag = 0;
		}
	}
	*ft_strnstr(ret, limiter, ft_strlen(ret)) = '\0';
	free (limiter);
	write(here_doc_fd, ret, ft_strlen(ret));
	close(here_doc_fd);
	here_doc_fd = open(HERE_DOC_INPUT_BUFFER, O_RDONLY);
	p->infile_fd = here_doc_fd;
	free(ret);
	return (0);
}

int	exec_fork(t_pcs *p, t_token_meta *meta, t_env *env)
{
	int		i;
	int		ret;
	int		pcs_cnt;
	int		stdinout_storage[2];
	t_token	*now;

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
		else if (now->type != ARG) //now == I_REDIR OR O_REDIR
			now = now->next->next;
		else //now == ARG
		{
			if (now->next->type == PIPE || now->next->type == I_REDIR || now->next->type == I_HRDOC) //NEXT == PIPE OR I_REDIR
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
	unlink(HERE_DOC_INPUT_BUFFER);
	reset_fds(p, stdinout_storage[0], stdinout_storage[1]);
	return (wait_for_children(p, p->pids, pcs_cnt));
}
