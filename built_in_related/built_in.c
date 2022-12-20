#include "../minishell.h"

int	is_built_in(char **com)
{
	if (!ft_strncmp(com[0], "echo", 4))
		return (ECHO);
	else if (!ft_strncmp(com[0], "cd", 2))
		return (CD);
	else if (!ft_strncmp(com[0], "pwd", 3))
		return (PWD);
	else if (!ft_strncmp(com[0], "export", 6))
		return (EXPORT);
	else if (!ft_strncmp(com[0], "unset", 5))
		return (UNSET);
	else if (!ft_strncmp(com[0], "env", 3))
		return (ENV);
	else if (!ft_strncmp(com[0], "exit", 4))
		return (EXIT);
	else
		return (0);
}

int	exec_built_in(char **com, t_env *env)
{
	int	ret;
	int	built_in_code;

	built_in_code = is_built_in(com);
	if (built_in_code == ECHO)
	{
		if (!ft_strncmp("-n", com[1], 3))
			g_exit_status = ft_echo(com[2], 1);
		else
			g_exit_status = ft_echo(com[1], 0);
	}
	else if (built_in_code == CD)
	 	g_exit_status = ft_cd(com[0], env);
	else if (built_in_code == PWD)
		g_exit_status = ft_pwd();
	else if (built_in_code == EXPORT)
		g_exit_status = ft_export(com[0], env);
	else if (built_in_code == UNSET)
		g_exit_status = ft_unset(com[0], env);
	else if (built_in_code == ENV)
		g_exit_status = ft_env(env);
	else if (built_in_code == EXIT)
		g_exit_status = ft_exit();
	return (g_exit_status);
}
