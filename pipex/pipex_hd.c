#include "pipex.h"
#include "libft.h"
#include <fcntl.h>
// ./pipex here_doc LIMITER cmd cmd1 file

static int	here_doc_seg(t_pcs *p, char *argv[])
{
	char	*limiter;
	int		here_doc_fd;
	char	*ret;
	char	*temp;
	int		fst_flag;
	char	buffer[10];
	char	*prev_nl;

	limiter = ft_strjoin(argv[2], "\n");
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

int	here_doc(t_pcs *p, int argc, char *argv[])
{
	int	i;

	if (here_doc_seg(p, argv))
		return (err_terminate(p));
	p->pids = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
	if (!p->pids)
		return (err_terminate(p));
	i = 2;
	while (i++ < argc - 2)
	{
		if (pipe(p->next_pfd) == -1)
			return (err_terminate(p));
		if (p->infile_fd == -1 && i == 3)
			close(p->next_pfd[1]);
		else
		{
			prep_fds(p, i, argc);
			p->pids[i - 3] = fork();
			if (p->pids[i - 3] == -1)
				return (err_terminate(p));
			else if (!p->pids[i - 3])
				exec_sh(p, argv, i);
		}
		swap_pfd(&p->next_pfd, &p->pfd);
	}
	unlink(HERE_DOC_INPUT_BUFFER);
	wait_for_children(p, p->pids, argc - 3);
	return (0);
}
