int	get_process()
{
	if (built_in)
	{
		exec_built_in();
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
