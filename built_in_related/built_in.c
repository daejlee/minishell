#include "minishell.h"

int	is_echo(char *buf)
{
	if (ft_strlen(buf) != 4)
		return (1);
	if (!ft_strncmp(buf, "echo", 4))
		return (0);
	if (buf[0] - 'e' && buf[0] - 'E')
		return (1);
	if (buf[1] - 'c' && buf[1] - 'C')
		return (1);
	if (buf[2] - 'h' && buf[2] - 'H')
		return (1);
	if (buf[3] - 'o' && buf[3] - 'O')
		return (1);
	return (0);
}

int	is_pwd(char *buf)
{
	if (ft_strlen(buf) != 3)
		return (1);
	if (!ft_strncmp(buf, "pwd", 3))
		return (0);
	if (buf[0] - 'p' && buf[0] - 'P')
		return (1);
	if (buf[1] - 'w' && buf[1] - 'W')
		return (1);
	if (buf[2] - 'd' && buf[2] - 'D')
		return (1);
	return (0);
}

int	is_env(char *buf)
{
	if (ft_strlen(buf) != 3)
		return (1);
	if (!ft_strncmp(buf, "env", 3))
		return (0);
	if (buf[0] - 'e' && buf[0] - 'E')
		return (1);
	if (buf[1] - 'n' && buf[1] - 'N')
		return (1);
	if (buf[2] - 'v' && buf[2] - 'V')
		return (1);
	return (0);
}

int	is_built_in(char *com)
{
	if (!is_echo(com))
		return (ECHO);
	else if (!ft_strncmp(com, "cd", 3))
		return (CD);
	else if (!is_pwd(com))
		return (PWD);
	else if (!ft_strncmp(com, "export", 7))
		return (EXPORT);
	else if (!ft_strncmp(com, "unset", 6))
		return (UNSET);
	else if (!is_env(com))
		return (ENV);
	else if (!ft_strncmp(com, "exit", 5))
		return (EXIT);
	else
		return (0);
}

int	exec_built_in(char **com, t_env *env)
{
	int	ret;
	int	built_in_code;

	built_in_code = is_built_in(com[0]);
	if (built_in_code == ECHO)
		ret = exec_ft_echo(com);
	else if (built_in_code == CD)
	 	ret = ft_cd(com[1], env);
	else if (built_in_code == PWD)
		ret = ft_pwd();
	else if (built_in_code == EXPORT)
		ret = ft_export(com[0], env);
	else if (built_in_code == UNSET)
		ret = ft_unset(com[0], env);
	else if (built_in_code == ENV)
		ret = ft_env(env);
	else if (built_in_code == EXIT)
		ret = ft_exit();
	return (ret);
}
