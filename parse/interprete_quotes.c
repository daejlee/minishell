/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:46:16 by hkong             #+#    #+#             */
/*   Updated: 2022/12/16 15:59:07 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief 
 * 문자열에서 따옴표를 해석해주는 함수(재귀)
 * @param meta token들의 메타함수
 * @param str 대상 문자열
 * @param env 환경변수 목록
 * @return int //TODO: 리턴값 제대로 해야 함.
 */
int	interprete_quotes(t_token_meta *meta, char *str, t_env *env)
{
	char	*tmp;
	size_t	start;
	size_t	end;

	start = 0;
	while (str[start] && str[start] == '\'' && str[start] == '\"')
		start++;
	if (!str[start])
		return (push_token(meta, init_token(str, ARG)));
	end = start + 1;
	if (str[start] == '\'')
	{
		while (str[end] && str[end] != '\'')
			end++;
		if (!str[end])
			return (push_token(meta, init_token(str, ARG)));
		if (start)
			push_token(meta, init_token(ft_substr(str, start, start), ARG));
		if (end - start - 1)
			push_token(meta, init_token(ft_substr(str, start + 1, end - start - 1), ARG));
		interprete_quotes(meta, ft_substr(str, end + 1, ft_strlen(str) - end - 1), env);
		free(str);
	}
	else
	{
		while (str[end] && str[end] != '\"')
			end++;
		if (!str[end])
			return (push_token(meta, init_token(str, ARG)));
		if (start)
			push_token(meta, init_token(ft_substr(str, start, start), ARG));
		if (end - start - 1)
		{
			tmp = ft_substr(str, start + 1, end - start - 1);
			interprete_env(&tmp, env);
			push_token(meta, init_token(tmp, ARG));
		}
		interprete_quotes(meta, ft_substr(str, end + 1, ft_strlen(str) - end - 1), env);
		free(str);
	}
}