/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:16:44 by hkong             #+#    #+#             */
/*   Updated: 2023/01/07 15:30:21 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief 
 * meta에 있는 모든 INIT인 토큰들에서 공백을 분리해주는 함수입니다.
 * @param meta 
 * @param env 
 * @return int 성공 시 0, 실패 시 1
 */
int	split_spaces(t_token_meta *meta, t_env *env)
{
	t_token	*node;
	size_t	token_num;
	size_t	index;

	index = 0;
	token_num = meta->size;
	while (index++ < token_num)
	{
		node = pop_token(meta);
		if (!node)
			return (print_error(UNEXPECTED, 0));
		if (node->type != INIT || !has_space(node->str) \
									|| has_heredoc_before(node, index))
		{
			push_token(meta, node);
			continue ;
		}
		if (split_spaces_in_substr(meta, node->str))
		{
			free_token(node);
			return (1);
		}
		free_token(node);
	}
	return (0);
}

/**
 * @brief 
 * 문자열에서 공백을 기준으로 토큰을 생성해주는 함수입니다.
 * @param meta 
 * @param str 
 * @return int 성공 시 0, 실패 시 1
 */
int	split_spaces_in_substr(t_token_meta *meta, char *str)
{
	size_t	start;
	size_t	end;

	initialize_numbers(&start, &end, NULL, NULL);
	while (str[end] || start != end)
	{
		if (str[end] && str[end] == ' ' && start == end)
			set_start_end(&start, &end, start + 1, end + 1);
		else if (str[end] && str[end] != ' ')
		{
			if (skip_quotes(str, &end))
				return (quote_syntax_error(str, end));
			set_start_end(NULL, &end, start, end + 1);
		}
		else
		{
			if (push_token(meta, init_token(ft_strdup(" "), BLANK)) || \
				push_token(meta, \
					init_token(ft_substr(str, start, end - start), INIT)))
				return (print_error(MALLOC_FAIL, 0));
			set_start_end(&start, NULL, end, end);
		}
	}
	return (0);
}

/**
 * @brief 
 * 따옴표 내부의 공백은 취급하지 않으므로,
 * 따옴표 안에 있는 문자열은 전부 스킵하는 함수입니다.
 * @param str 
 * @param end 
 * @return int 쌍이 맞지 않을 시 1, 성공 시 0
 */
int	skip_quotes(char *str, size_t *end)
{
	size_t	index;

	index = *end;
	if (str[index] == '\'')
		while (str[++index] && str[index] != '\'')
			;
	if (str[index] == '\"')
		while (str[++index] && str[index] != '\"')
			;
	if (!str[index])
		return (1);
	*end = index;
	return (0);
}

/**
 * @brief 
 * 이전에 heredoc이 있다면 원본을 유지하기 위해 해석한 환경변수의 공백을 구분하지 않습니다.
 * 따라서 현재 토큰의 이전에 I_HRDOC 타입의 토큰이 있는 지 확인하는 함수입니다.
 * (공백은 건너뜀)
 * @param token 
 * @return int 있으면 1, 없으면 0
 */
int	has_heredoc_before(t_token *token, size_t index)
{
	t_token	*node;

	node = token;
	if (index == 0)
		return (0);
	while ((index-- - 1) && node->prev->type == BLANK)
		node = node->prev;
	if (node->prev->type == I_HRDOC)
		return (1);
	return (0);
}

/**
 * @brief 
 * 해당 문자열에 공백이 있는 지 찾는 함수
 * @param str 
 * @return int 공백이 있으면 1, 없으면 0
 */
int	has_space(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == ' ')
			return (1);
		index++;
	}
	return (0);
}
