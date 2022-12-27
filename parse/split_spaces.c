/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:16:44 by hkong             #+#    #+#             */
/*   Updated: 2022/12/27 17:37:53 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	token_num = meta->size;
	while (token_num--)
	{
		node = pop_token(meta);
		if (!node)
			return (1);
		if (node->type != INIT)
		{
			push_token(meta, node);
			continue ;
		}
		if (split_spaces_in_substr(meta, node->str))
		{
			free_token(node);
			return (print_error(MALLOC_FAIL, 0));
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
	size_t	flag;

	initialize_numbers(&start, &end, &flag, NULL);
	while (str[end] || start != end)
	{
		if (str[end] && str[end] == ' ' && start == end)
			set_start_end(&start, &end, start + 1, end + 1);
		else if (str[end] && str[end] != ' ')
		{
			if (skip_quotes(str, &end))
				return (print_error(SYNTAX_ERROR, str[end - 1]));
			set_start_end(NULL, &end, start, end + 1);
		}
		else
		{
			if (flag++ && push_token(meta, init_token(ft_strdup(" "), BLANK)))
				return (print_error(MALLOC_FAIL, 0));
			if (push_token(meta, \
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
	if (str[*end] == '\'')
		while (str[++(*end)] && str[*end] != '\'')
			;
	if (str[*end] == '\"')
		while (str[++(*end)] && str[*end] != '\"')
			;
	if (!str[*end])
		return (1);
	return (0);
}
