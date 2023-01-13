/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:30:54 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 17:25:24 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/**
 * @brief 
 * 빌트인 echo 함수입니다. -n 옵션을 지원합니다.
 * original : echo [-n] [string ...]
 * @param com command 이차원 배열
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_echo(char **com)
{
	char	*str;
	int		n_option;

	if (com[1])
	{
		n_option = get_n_option(com);
		str = get_echo_str(com, n_option);
		if (!str)
			print_error(MALLOC_FAIL, NULL);
		write(1, str, ft_strlen(str));
		free(str);
	}
	else
		write(1, "\n", 1);
	return (0);
}

/**
 * @brief 
 * -n 옵션이 있는 지, 있다면 어디까지인 지 확인하는 함수 
 * @return int -n 옵션이 없는 인덱스 - 1
 */
int	get_n_option(char **com)
{
	int	index;
	int	k;

	if (ft_strncmp(com[0], "echo", 4))
	{
		if (!ft_strncmp(com[1], "-n", 3))
			return (1);
		return (0);
	}
	index = 1;
	while (com[index] && !ft_strncmp(com[index], "-n", 2))
	{
		k = 2;
		while (com[index][k])
		{
			if (com[index][k] != 'n')
				return (index - 1);
			k++;
		}
		index++;
	}
	return (index - 1);
}

/**
 * @brief 
 * echo로 출력될 문자열을 리턴하는 함수
 * @return char * 성공 시 문자열, 실패 시 NULL
 */
char	*get_echo_str(char **com, int n_option)
{
	char	*result;
	char	*temp;
	int		index;

	index = n_option + 1;
	if (!com[index])
		return (NULL);
	result = ft_strdup(com[index++]);
	if (!result)
		print_error(MALLOC_FAIL, NULL);
	while (com[index])
	{
		temp = result;
		result = ft_strjoin_modified(result, com[index++], ' ');
		free(temp);
		if (!result)
			return (NULL);
	}
	if (!n_option)
	{
		temp = result;
		result = ft_strjoin(result, "\n");
		free(temp);
	}
	return (result);
}
