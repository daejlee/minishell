/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:26:07 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 12:55:28 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static char	**get_sh_path(t_env *env, int *no_path_flag)
{
	unsigned int	i;
	int				fst_flag;
	char			**sh_paths;
	t_env			*now;

	i = 0;
	now = env;
	fst_flag = 1;
	while (now != env || fst_flag)
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
		fst_flag = 0;
	}
	*no_path_flag = 1;
	return (NULL);
}

static char	*get_sh_func(char **com, t_env *env, int *no_path_flag)
{
	char			*sh_func;
	char			**sh_paths;
	unsigned int	i;

	i = 0;
	sh_paths = get_sh_path(env, no_path_flag);
	if (*no_path_flag)
		return (NULL);
	if (!sh_paths)
		return (NULL);
	while (sh_paths[i])
	{
		sh_func = ft_strjoin_modified(sh_paths[i++], com[0], '/');
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
		err_terminate(p);
	}
	execve((const char *)sh_func, (char *const *)p->com, p->envp);
	execve_failed(p, sh_func);
}

t_token	*prep_fd_n_move(t_token *now, int i, t_token_meta *meta, t_pcs *p)
{
	if (now == meta->head)
		now = now->next;
	while (now->type != PIPE && now != meta->head)
		now = now->next;
	if (now->type == PIPE && i == p->pcs_cnt - 1)
		now = now->next;
	prep_fds(p, i, p->pcs_cnt, meta);
	return (now);
}

int	prep_exec_loop(t_pcs *p, t_token_meta *meta)
{
	p->pcs_cnt = get_pcs_cnt(meta);
	p->pids = (pid_t *)malloc(sizeof(pid_t) * (p->pcs_cnt));
	if (!p->pids)
		err_terminate(p);
	p->pfd_arr = (int **)malloc(sizeof (int *) * (p->pcs_cnt));
	if (!p->pfd_arr)
		err_terminate(p);
	if (get_pipes(p, p->pcs_cnt))
		err_terminate(p);
	p->stdinout_storage[0] = dup(0);
	p->stdinout_storage[1] = dup(1);
	p->hdb_idx = 0;
	return (0);
}
