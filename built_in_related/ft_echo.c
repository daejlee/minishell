/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:30:54 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/10 16:37:03 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_n_option_seg(char **com, int *n_flag_adr, int i)
{
	int	k;

	while (!ft_strncmp(com[i], "-n", 2))
	{
		k = 2;
		while (com[i][k])
		{
			if (com[i][k] != 'n')
				return (i);
			k++;
		}
		*n_flag_adr = 1;
		i++;
	}
	if (i == 1)
	{
		*n_flag_adr = 0;
		return (0);
	}
	return (i);
}

int	get_n_option(char **com, int *n_flag_adr)
{
	int	i;
	int	ret;

	i = 1;
	if (!ft_strncmp(com[0], "echo", 4))
		return (get_n_option_seg(com, n_flag_adr, i));
	else
	{
		if (!ft_strncmp(com[1], "-n", 3))
		{
			*n_flag_adr = 1;
			return (1);
		}
		*n_flag_adr = 0;
		return (0);
	}
}

char	*get_echo_buf(char **com, int n_option)
{
	char	*ret;
	char	*temp;
	int		i;
	int		fst_flag;

	fst_flag = 1;
	i = 1;
	if (n_option)
		i += (n_option - 1);
	ret = "";
	while (com[i])
	{
		if (!fst_flag)
		{
			if (temp)
				free(temp);
			ret = ft_strjoin_modified(ret, com[i], ' ');
			temp = ret;
		}
		else
			ret = com[i];
		fst_flag = 0;
		i++;
	}
	return (ret);
}

int	exec_ft_echo(char **com)
{
	char	*buf;
	int		n_option;
	int		n_flag;

	if (!com[1])
		return (ft_echo("", 0));
	n_flag = 0;
	n_option = get_n_option(com, &n_flag);
	buf = get_echo_buf(com, n_option);
	if (!buf)
		return (-1);
	return (ft_echo(buf, n_flag));
}

/**
 * @brief 
 * 빌트인 echo 함수입니다. -n 옵션을 지원합니다.
 * original : echo [-n] [string ...]
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_echo(char *buf, int n_flag)
{
	char	*printing_buf;

	if (n_flag)
		printing_buf = ft_strjoin(buf, "");
	else
		printing_buf = ft_strjoin(buf, "\n");
	if (!printing_buf)
		return (-1);
	write(1, printing_buf, ft_strlen(printing_buf));
	return (0);
}
