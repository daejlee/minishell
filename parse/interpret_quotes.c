/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:46:16 by hkong             #+#    #+#             */
/*   Updated: 2022/12/16 17:36:51 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief 
 * 문자열에서 따옴표를 해석해주는 함수(재귀)
 * @param meta token들의 메타함수
 * @param str 대상 문자열
 * @param env 환경변수 목록
 * @return int 성공 시 0, 실패 시 1
 */
int	interpret_quotes(t_token_meta *meta, char *str, t_env *env)
{
	char	*next_str;
	size_t	start;
	size_t	end;

	start = 0;
	while (str[start] && str[start] == '\'' && str[start] == '\"')
		start++;
	if (!str[start])
		return (push_token(meta, init_token(str, INIT)));
	end = start + 1;
	if (str[start] == '\'')
		end = interpret_quotes_single(meta, str, start);
	else
		end = interpret_quotes_double(meta, env, str, start);
	next_str = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	free(str);
	if (!next_str)
		return (1);
	return (interpret_quotes(meta, next_str, env));
}

/**
 * @brief 
 * single quote을 처리하는 함수입니다.
 * @param meta 
 * @param str 
 * @param start 처음 나타나는 single quote의 인덱스
 * @return int 실패 시 0, 성공 시 end의 인덱스를 반환합니다.
 */
int	interpret_quotes_single(t_token_meta *meta, char *str, size_t start)
{
	size_t	end;

	end = start + 1;
	while (str[end] && str[end] != '\'')
		end++;
	if (!str[end])
	{
		if (push_token(meta, init_token(str, INIT)))
			return (0);
		else
			return (end);
	}
	if (start)
		if (push_token(meta, init_token(ft_substr(str, start, start), INIT)))
			return (0);
	if (end - start - 1)
		if (push_token(meta, \
				init_token(ft_substr(str, start + 1, end - start - 1), ARG)))
			return (0);
	return (end);
}

/**
 * @brief 
 * double quote을 처리하는 함수입니다.
 * @param meta 
 * @param env
 * @param str 
 * @param start 처음 나타나는 double quote의 인덱스
 * @return int 실패 시 0, 성공 시 end의 인덱스를 반환합니다.
 */
int	interpret_quotes_double(t_token_meta *meta, \
											t_env *env, char *str, size_t start)
{
	size_t	end;
	char	*sub;

	while (str[end] && str[end] != '\'')
		(end)++;
	if (!str[end])
	{
		if (push_token(meta, init_token(str, INIT)))
			return (0);
		else
			return (end);
	}
	if (start)
		if (push_token(meta, init_token(ft_substr(str, start, start), INIT)))
			return (0);
	if (end - start - 1)
	{
		sub = ft_substr(str, start + 1, end - start - 1);
		if (!sub)
			return (0);
		interpret_env(&sub, env);
		//TODO: 리턴값 생각하기
		if (push_token(meta, init_token(sub, ARG)))
			return (0);
	}
	return (end);
}
