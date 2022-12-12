#include "../minishell.h"

int	is_built_in(char *com)
{
	if (!ft_strncmp(com, "echo", 4))
		return (echo);
	else if (!ft_strncmp(com, "cd", 2))
		return (cd);
	else if (!ft_strncmp(com, "pwd", 3))
		return (pwd);
	else if (!ft_strncmp(com, "export", 6))
		return (export);
	else if (!ft_strncmp(com, "unset", 5))
		return (unset);
	else if (!ft_strncmp(com, "env", 3))
		return (env);
	else if (!ft_strncmp(com, "exit", 4))
		return (exit);
	else
		return (0);
}

int	exec_built_in(int built_in_code)
{
	int	ret;
	if (built_in_code == echo)
		g_exit_status = ft_echo(buf, n_option);
	else if (built_in_code == cd)
	else if (built_in_code == pwd)
	else if (built_in_code == export)
	else if (built_in_code == unset)
	else if (built_in_code == env)
	else if (built_in_code == exit)
}
