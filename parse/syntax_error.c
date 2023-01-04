/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:01:41 by hkong             #+#    #+#             */
/*   Updated: 2023/01/04 21:47:57 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief 
 * 노드를 순회하며 존재하는 syntax error를 처리해준다.
 * @return int 정상 0, 에러가 있을 시 1
 */
int	syntax_error(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;

	token_num = meta->size;
	node = meta->head;
	while (token_num--)
	{
		if (node->type == PIPE)
			if (syntax_error_pipe(meta, token_num, node))
				return (1);
		if (node->type == I_REDIR || node->type == I_HRDOC || \
					node->type == O_REDIR || node->type == O_APPND)
			if (syntax_error_redir(token_num, node, node->type))
				return (1);
		node = node->next;
	}
	return (0);
}

/**
 * @brief 
 * 현재 node가 redir일 시, 가능한 syntax error를 처리해준다.
 * @return int 정상 0, 에러가 있을 시 1
 */
int	syntax_error_redir(size_t token_num, t_token *node, enum e_token_type type)
{
	if (!token_num)
		return (print_error(SYNTAX_ERROR, "newline"));
	else if (node->next->type == EMPTY)
	{
		if (type != I_HRDOC)
			return (print_error(AMBIGUOUS_REDIR, node->next->origin_str));
	}
	else if (node->next->type != ARG)
		return (print_error(SYNTAX_ERROR, node->next->str));
	return (0);
}

/**
 * @brief 
 * 현재 node가 pipe일 시, 가능한 syntax error를 처리해준다.
 * @return int 정상 0, 에러가 있을 시 1
 */
int	syntax_error_pipe(t_token_meta *meta, size_t token_num, t_token *node)
{
	if (token_num == meta->size - 1)
		return (print_error(SYNTAX_ERROR, node->str));
	else if (!token_num)
		return (print_error(SYNTAX_ERROR, "newline"));
	return (0);
}
