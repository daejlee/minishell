#include "minishell.h"
#include "libft.h"

int	get_process(t_token_meta *meta)
{
	pid_t	*pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * com_num);
	if (!pids)
		return (-1);
	while (com_num--)
	{
		if (is_built_in(com))
		{
			exec_built_in(is_built_in(com));
			if (exit)
				return (g_exit_status);
			else
				return (0);
		}
		pid = fork();
		if (!pid)
		{
			if (has pipe)
			{
				pipe_handle;
				exec_com;
				return (0);
			}
			else
			{
				exec_com_like_bin/ls;
				return (0);
			}
		}
	}
}
