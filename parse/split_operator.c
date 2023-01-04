/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:23:58 by hkong             #+#    #+#             */
/*   Updated: 2022/12/22 18:37:57 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * meta에 있는 모든 INIT인 토큰들에서 pipe 및 redirection을 분리해주는 함수입니다. 
 * @param meta 
 * @return int 성공 시 0, 실패 시 1
 */
int	split_operator(t_token_meta *meta)
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
		index = operator_index(node->str);
		if (!index || node->type != INIT)
		{
			push_token(meta, node);
			continue ;
		}
		free(node->origin_str);
		if (split_operator_in_substr(meta, node->str))
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
 * string에서 pipe 및 redirection을 분리해주는 함수입니다.
 * @param meta 
 * @param str 
 * @return int 성공 시 0, 실패 시 1
 */
int	split_operator_in_substr(t_token_meta *meta, char *str)
{
	size_t	index;

	index = operator_index(str);
	if (!index)
		return (push_token(meta, init_token(str, INIT)));
	index--;
	if (index)
		if (push_token(meta, init_token(ft_substr(str, 0, index), INIT)))
			return (fail_and_free_multiple_str(str, NULL, NULL, NULL));
	if (push_token(meta, create_operator_token(str, &index)))
		return (fail_and_free_multiple_str(str, NULL, NULL, NULL));
	if (index + 1 != ft_strlen(str))
		if (split_operator_in_substr(meta, \
				ft_substr(str, index + 1, ft_strlen(str) - index - 1)))
			return (fail_and_free_multiple_str(str, NULL, NULL, NULL));
	return (ok_and_free_multiple_str(str, NULL, NULL, NULL));
}

/**
 * @brief 
 * string에서 pipe 및 redirection이 나타나는 index를 알려주는 함수입니다.
 * @param str 
 * @return size_t 없을 시 0, 있을 시 index + 1 반환
 */
size_t	operator_index(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '<')
			return (index + 1);
		else if (str[index] == '>')
			return (index + 1);
		else if (str[index] == '|')
			return (index + 1);
		index++;
	}
	return (0);
}

/**
 * @brief 
 * 해당 위치에 있는 pipe 및 redirecion의 type을 알려주는 함수입니다.
 * @param str 
 * @return enum e_token_type 
 */
enum e_token_type	operator_type(char *str)
{
	if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (I_HRDOC);
		return (I_REDIR);
	}
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (O_APPND);
		return (O_REDIR);
	}
	return (PIPE);
}

/**
 * @brief
 * 문자열의 인덱스에 존재하는 pipe 및 redirecion의 타입에 맞추어 토큰을 생성해주고,
 * 길이가 2인 redirecion의 경우 index값을 뒤로 미뤄주는 함수. 
 * @param str 
 * @param index 
 * @return t_token* 실패 시 NULL
 */
t_token	*create_operator_token(char *str, size_t *index)
{
	t_token				*node;
	char				*node_str;
	enum e_token_type	type;

	type = operator_type(str + *index);
	if (type == I_REDIR)
		node_str = ft_strdup("<");
	else if (type == I_HRDOC)
	{
		node_str = ft_strdup("<<");
		(*index)++;
	}
	else if (type == O_REDIR)
		node_str = ft_strdup(">");
	else if (type == O_APPND)
	{
		node_str = ft_strdup(">>");
		(*index)++;
	}
	else
		node_str = ft_strdup("|");
	node = init_token(node_str, type);
	return (node);
}
