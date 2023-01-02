/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:39:35 by hkong             #+#    #+#             */
/*   Updated: 2023/01/02 21:22:20 by hkong            ###   ########.fr       */
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
			return (print_error(UNEXPECTED, 0));
		if (node->type == INIT)
		{
			if (interpret_env_in_substr(&(node->str), env))
			{
				free_token(node);
				return (print_error(MALLOC_FAIL, 0));
			}
			check_set_env_node(node, token_num);
		}
		push_token(meta, node);
	}
	return (0);
}

/**
 * @brief 
 * env 해석을 마친 노드에 후처리를 해주는 함수입니다.
 * 비어있을 시, EMPTY타입 지정해주고,
 * 마지막이 $이면서 다음에 따옴표가 있을 시 $을 삭제해줍니다.
 * @param node 
 * @param token_num 
 */
void	check_set_env_node(t_token *node, size_t token_num)
{
	if (!ft_strlen(node->str))
		node->type = EMPTY;
	else if (token_num && node->str[ft_strlen(node->str) - 1] == '$' \
						&& node->next->type == ARG || node->next->type == EMPTY)
	{
		node->str[ft_strlen(node->str) - 1] = '\0';
		node->origin_str[ft_strlen(node->origin_str) - 1] = '\0';
	}
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
	free(*str);
	result_tmp = ft_strjoin(front, value);
	result = ft_strjoin(result_tmp, back);
	if (!(front && back && result_tmp && result))
		return (fail_and_free_multiple_str(front, back, result_tmp, result));
	ok_and_free_multiple_str(front, back, result_tmp, NULL);
	*str = result;
	return (0);
}
