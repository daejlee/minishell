/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:54:38 by daejlee           #+#    #+#             */
/*   Updated: 2022/08/13 19:54:38 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <sys/wait.h>

void	init_p(t_pcs *p)
{
	p->here_doc_flag = 0;
	p->outfile_fd = 0;
	p->infile_fd = 0;
	// p->pfd[0] = 0;
	// p->pfd[1] = 0;
	// (p->pfd + 1)[0] = 0;
	// (p->pfd + 1)[1] = 0;
	p->pfd = NULL;
	p->next_pfd = NULL;
	p->envp = NULL;
	p->com = NULL;
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
