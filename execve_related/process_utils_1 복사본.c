#include "../minishell.h"
#include "./process.h"

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
