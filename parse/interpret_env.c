/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:39:35 by hkong             #+#    #+#             */
/*   Updated: 2022/12/29 16:15:59 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief 
 * meta에 있는 모든 토큰들에 있는 환경변수를 해석해주는 함수.
 * 이 때 토큰의 타입은 INIT이어야 한다.
 * 또한 해석 이후 비어 있는 토큰은 ARG로 타입을 변환해준다.
 * @param meta 
 * @param env 
 * @return int 성공 시 0, 실패 시 1
 */
int	interpret_env(t_token_meta *meta, t_env *env)
{
	t_token	*node;
	size_t	token_num;

	token_num = meta->size;
	while (token_num--)
	{
		node = pop_token(meta);
		if (!node)
			return (1);
		if (node->type == INIT && interpret_env_in_substr(&(node->str), env))
		{
			free_token(node);
			return (print_error(MALLOC_FAIL, 0));
		}
		if (!ft_strlen(node->str))
			node->type = ARG;
		push_token(meta, node);
	}
	return (0);
}

/**
 * @brief 
 * string에서 환경변수로 해석되어야 할 부분을 확인해 바꿔준다.
 * @param str 대상 string
 * @param env 환경변수 목록
 * @return int 성공 시 0, 실패 시 1
 */
int	interpret_env_in_substr(char **str, t_env *env)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (!*str)
		return (1);
	while ((*str)[start])
	{
		if ((*str)[start] == '$')
		{
			end = start + 1;
			while ((*str)[end] && \
					is_env_allowed_char(end == start + 1, (*str)[end]) &&
					(*str)[end - 1] != '?')
				end++;
			if (end != start + 1)
				if (change_key_to_value(str, env, &start, end))
					return (1);
		}
		start++;
	}
	return (0);
}

/**
 * @brief 
 * 환경변수로 해석될 수 있는 key값을 찾았을 때, 이를 value로 바꿔준다.
 * @param str 
 * @param env 
 * @param start '$'의 인덱스
 * @param end 해석될 수 있는 마지막 부분의 다음 인덱스
 * @return int 성공 시 0, 실패 시 1
 */
int	change_key_to_value(char **str, t_env *env, size_t *start, size_t end)
{
	t_env	*node;
	char	*key;
	char	*value;

	key = ft_substr(*str, *start + 1, end - *start - 1);
	if (is_exactly_same(key, "?"))
		value = ft_itoa(g_exit_status);
	else
	{
		node = find_env(env, key);
		if (node)
			value = ft_strdup(node->value);
		else
			value = ft_strdup("");
	}
	if (!key || !value || insert_value_on_index(str, value, *start, end))
		return (fail_and_free_multiple_str(value, key, NULL, NULL));
	*start = end + ft_strlen(value) - ft_strlen(key) - 1;
	return (ok_and_free_multiple_str(value, key, NULL, NULL));
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
int	insert_value_on_index(char **str, char *value, size_t start, size_t end)
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
		return (fail_and_free_multiple_str(front, back, result_tmp, result));
	ok_and_free_multiple_str(front, back, result_tmp, *str);
	*str = result;
	return (0);
}

/**
 * @brief 
 * env key에 허용되는 char인지 확인해주는 함수
 * @param is_first 맨 처음에는 숫자가 올 수 없고, ?이 올 수 있기에 확인을 위해 사용한다.
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
	if (is_first && c == '?')
		return (1);
	return (0);
}
