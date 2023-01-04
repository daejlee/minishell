/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:23:23 by hkong             #+#    #+#             */
/*   Updated: 2023/01/04 19:38:17 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief 
 * 변환이 이루어지지 않은 모든 INIT 토큰들을 ARG 토큰으로 바꿔준다.
 * @param meta 
 * @return int 성공 시 0, 실패 시 1
 */
int	modify_init_to_arg(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;

	if (!meta)
		return (print_error(UNEXPECTED, 0));
	token_num = meta->size;
	node = meta->head;
	while (token_num--)
	{
		if (!node)
			return (print_error(UNEXPECTED, 0));
		if (node->type == INIT)
			node->type = ARG;
		node = node->next;
	}
	return (0);
}

/**
 * @brief 
 * 연속된 ARG/EMPTY 토큰들을 하나로 합쳐준다. 
 * @param meta 
 * @return int 성공 시 0, 실패 시 1
 */
int	union_args_to_one(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;
	t_token	*new_node;

	if (!meta)
		return (print_error(UNEXPECTED, 0));
	token_num = meta->size;
	while (token_num--)
	{
		node = pop_token(meta);
		if (!node)
			return (print_error(UNEXPECTED, 0));
		if (token_num && (node->type == ARG || node->type == EMPTY) && \
						(node->next->type == ARG || node->next->type == EMPTY))
		{
			new_node = create_union_token(&token_num, meta, node);
			if (!new_node)
				return (print_error(MALLOC_FAIL, 0));
			push_token(meta, new_node);
		}
		else
			push_token(meta, node);
	}
	return (0);
}

/**
 * @brief 
 * 해당 노드부터 연속된 arg, empty 토큰들을 하나로 만들어 token을 생성해 리턴한다.
 * @param meta 
 * @return int 성공 시 만들어진 토큰, 실패 시 NULL
 */
t_token	*create_union_token(size_t *num, t_token_meta *meta, t_token *node)
{
	t_token	*result;
	char	*str;
	char	*origin_str;

	str = NULL;
	origin_str = NULL;
	if (set_two_string(&str, ft_strdup(node->str), \
									&origin_str, ft_strdup(node->origin_str)))
		return (NULL);
	while ((*num) && (node->next->type == ARG || node->next->type == EMPTY))
	{
		free_token(node);
		node = pop_token(meta);
		(*num)--;
		if (set_two_string(&str, ft_strjoin(str, node->str), \
						&origin_str, ft_strjoin(origin_str, node->origin_str)))
			return (NULL);
	}
	free_token(node);
	result = init_token(str, ARG);
	if (!result)
		return (ok_and_free_multiple_str(str, origin_str, NULL, NULL));
	set_token_origin(result, origin_str);
	return (result);
}

/**
 * @brief 
 * 더 이상 의미가 없는 space token을 제거해주는 함수
 * @param meta 
 * @return int 성공 시 0, 실패 시 1
 */
int	delete_space_token(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;

	if (!meta)
		return (print_error(UNEXPECTED, 0));
	token_num = meta->size;
	while (token_num--)
	{
		node = pop_token(meta);
		if (!node)
			return (print_error(UNEXPECTED, 0));
		if (node->type == BLANK)
			free_token(node);
		else
			push_token(meta, node);
	}
	return (0);
}
