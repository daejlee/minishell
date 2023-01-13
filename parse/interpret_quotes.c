/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:46:16 by hkong             #+#    #+#             */
/*   Updated: 2023/01/13 15:44:19 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief 
 * 공백으로 구분된 토큰들에서 따옴표가 있는 토큰들을 처리해주는 함수.
 * 전제조건: 모든 토큰들 중에서 str이 NULL인 토큰은 없음.
 * @param meta token들의 메타
 * @param env 환경변수 목록
 * @return int 성공 시 0, 실패 시 1
 */
int	interpret_quotes(t_token_meta *meta, t_env *env)
{
	t_token	*node;
	size_t	token_num;
	size_t	index;

	token_num = meta->size;
	while (token_num--)
	{
		node = pop_token(meta);
		if (!node)
			return (print_error(UNEXPECTED, 0));
		index = quote_index(node->str);
		if (!index)
		{
			push_token(meta, node);
			continue ;
		}
		free(node->origin_str);
		if (interpret_quotes_in_substr(meta, node->str, env))
		{
			free(node);
			return (print_error(MALLOC_FAIL, 0));
		}
		free(node);
	}
	return (0);
}

/**
 * @brief 
 * 문자열에서 따옴표를 해석해주는 함수(재귀)
 * 전제조건: str은 NULL이 아님.
 * @param meta token들의 메타함수
 * @param str 대상 문자열
 * @param env 환경변수 목록
 * @return int 성공 시 0, 실패 시 1
 */
int	interpret_quotes_in_substr(t_token_meta *meta, char *str, t_env *env)
{
	char	*next_str;
	size_t	start;

	start = quote_index(str);
	if (!start)
		return (push_token(meta, init_token(str, INIT)));
	start--;
	if (str[start] == '\'')
		next_str = interpret_quotes_single(meta, str, start);
	else
		next_str = interpret_quotes_double(meta, env, str, start);
	free(str);
	if (!next_str)
		return (1);
	if (!ft_strlen(next_str))
		return (ok_and_free_multiple_str(next_str, NULL, NULL, NULL));
	return (interpret_quotes_in_substr(meta, next_str, env));
}

/**
 * @brief 
 * single quote을 처리하는 함수입니다.
 * @param meta 
 * @param str 
 * @param start 처음 나타나는 single quote의 인덱스
 * @return char * 실패 시 NULL, 성공 시 따옴표 이후의 string을 반환합니다.
 */
char	*interpret_quotes_single(t_token_meta *meta, char *str, size_t start)
{
	size_t	end;
	char	*next_str;

	end = start + 1;
	while (str[end] && str[end] != '\'')
		end++;
	if (start)
		if (push_token(meta, init_token(ft_substr(str, 0, start), INIT)))
			return (0);
	if (!(end - start - 1))
	{
		if (push_token(meta, init_token(ft_strdup(""), ARG)))
			return (0);
	}
	else if (push_token(meta, \
				init_token(ft_substr(str, start + 1, end - start - 1), ARG)))
		return (0);
	next_str = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	return (next_str);
}

/**
 * @brief 
 * double quote을 처리하는 함수입니다.
 * @param meta 
 * @param env
 * @param str 
 * @param start 처음 나타나는 double quote의 인덱스
 * @return char * 실패 시 NULL, 성공 시 따옴표 이후의 string을 반환합니다.
 */
char	*interpret_quotes_double(t_token_meta *meta, \
											t_env *env, char *str, size_t start)
{
	t_token	*node;
	size_t	end;
	char	*next_str;

	end = start + 1;
	while (str[end] && str[end] != '\"')
		end++;
	if (start)
		if (push_token(meta, init_token(ft_substr(str, 0, start), INIT)))
			return (0);
	node = init_token(ft_substr(str, start + 1, end - start - 1), ARG);
	if (!node)
		return (0);
	if (interpret_env_in_substr(&(node->str), env))
	{
		free_token(node);
		return (0);
	}
	if (push_token(meta, node))
		return (0);
	next_str = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	return (next_str);
}

/**
 * @brief 
 * 문자열에서 따옴표의 위치를 반환하는 함수입니다.
 * @param str 
 * @return size_t 없을 시 0, 있을 시 index + 1 반환
 */
size_t	quote_index(char *str)
{
	size_t	start;

	start = 0;
	while (str[start] && str[start] != '\'' && str[start] != '\"')
		start++;
	if (!str[start])
		return (0);
	return (start + 1);
}
