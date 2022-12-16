/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:39:35 by hkong             #+#    #+#             */
/*   Updated: 2022/12/16 15:45:05 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief 
 * string에서 환경변수로 해석되어야 할 부분을 확인해 바꿔준다.
 * @param str 대상 string
 * @param env 환경변수 목록
 */
void	interprete_env(char **str, t_env *env)
{
	size_t	start;
	size_t	end;
	char	*key;
	char	*value;
	t_env	*node;

	start = 0;
	while ((*str)[start])
	{
		if ((*str)[start] == '$')
		{
			end = start + 1;
			while ((*str)[end] && is_env_allowed_char(end == start + 1, (*str)[end]))
				end++;
			if (end == start + 1)
			{
				start++;
				continue ;
			}
			key = ft_substr(*str, start + 1, end - start - 1);
			//! null guard
			node = find_env(env, key);
			if (node)
				value = ft_strdup(node->value);
			else
				value = ft_strdup("");
			//! null guard
			change_key_to_value(str, value, start, end);
			//! error check
			start = end + ft_strlen(value) - ft_strlen(key);
			free_multiple_str(value, key, NULL, NULL);
		}
		start++;
	}
}

/**
 * @brief 
 * 전체 string에서 env의 key 값을 value 값으로 바꿔준다.
 * @param str 전체 string
 * @param value 들어가게 될 value
 * @param start string에서 key값의 시작 인덱스
 * @param end string에서 key값의 끝 + 1 인덱스
 * @return int 성공이면 0, 실패면 1
 */
int	change_key_to_value(char **str, char *value, size_t start, size_t end)
{
	char	*result;
	char	*result_tmp;
	char	*front;
	char	*back;

	if (!value || !*str)
		return (1);
	front = ft_substr(*str, 0, start);
	back = ft_substr(*str, end, ft_strlen(*str) - end);
	result_tmp = ft_strjoin(front, value);
	result = ft_strjoin(result_tmp, back);
	if (!(front && back && result_tmp && result))
	{
		free_multiple_str(front, back, result_tmp, result);
		return (1);
	}
	free_multiple_str(front, back, result_tmp, *str);
	*str = result;
	return (0);
}

/**
 * @brief 
 * env key에 허용되는 char인지 확인해주는 함수
 * @param is_first 맨 처음에는 숫자가 올 수 없기에 확인을 위해 사용한다.
 * @param c 확인하고자 하는 char
 * @return int 올바른 값이면 1 아니면 0
 */
int	is_env_allowed_char(int is_first, char c)
{
	if (c == '_')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (!is_first && c >= '0' && c <= '9')
		return (1);
	return (0);
}
