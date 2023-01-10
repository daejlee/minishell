/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:25:19 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/10 16:37:15 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
