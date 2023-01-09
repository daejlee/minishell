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
		return (B_ECHO);
	else if (!ft_strncmp(com, "cd", 3))
		return (B_CD);
	else if (!is_pwd(com))
		return (B_PWD);
	else if (!ft_strncmp(com, "export", 7))
		return (B_EXPORT);
	else if (!ft_strncmp(com, "unset", 6))
		return (B_UNSET);
	else if (!is_env(com))
		return (B_ENV);
	else if (!ft_strncmp(com, "exit", 5))
		return (B_EXIT);
	else
		return (0);
}

int	exec_built_in(char **com, t_env *env)
{
	int	ret;
	int	built_in_code;
	int	i;

	i = 1;
	built_in_code = is_built_in(com[0]);
	if (built_in_code == B_ECHO)
		ret = exec_ft_echo(com);
	else if (built_in_code == B_CD)
	 	ret = ft_cd(com[1], env);
	else if (built_in_code == B_PWD)
		ret = ft_pwd();
	else if (built_in_code == B_EXPORT)
	{
		if (!com[i])
			ret = ft_export(NULL, env);
		else
		{
			while (com[i])
				ret = ft_export(com[i++], env);
		}
	}
	else if (built_in_code == B_UNSET)
	{
		while (com[i])
			ret = ft_unset(com[i++], env);
	}
	else if (built_in_code == B_ENV)
		ret = ft_env(env);
	else if (built_in_code == B_EXIT)
		ret = ft_exit();
	return (ret);
}
