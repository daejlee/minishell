/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:23:23 by hkong             #+#    #+#             */
/*   Updated: 2023/01/06 13:25:07 by hkong            ###   ########.fr       */
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
 * 더 이상 의미가 없는 space token을 제거해주는 함수
 * @param meta 
 * @return int 성공 시 0, 실패 시 1
 */
int	delete_space_token(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;

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

/**
 * @brief 
 * 명령어 사이에 의미 없는 EMPTY 토큰이 있을 때, 해당 토큰을 제거해주는 함수
 * @param meta 
 * @return int 성공 시 0, 실패 시 1
 */
int	delete_empty_token(t_token_meta *meta)
{
	size_t	token_num;
	size_t	index;
	t_token	*node;

	token_num = meta->size;
	index = 0;
	while (index++ < token_num)
	{
		node = pop_token(meta);
		if (!node)
			return (print_error(UNEXPECTED, 0));
		if (node->type == EMPTY)
		{
			if ((index != 1 && node->prev->type != PIPE) || \
				(index != token_num && node->next->type != PIPE))
			{
				free_token(node);
				continue ;
			}
		}
		push_token(meta, node);
	}
	return (0);
}

/**
 * @brief 
 * here_doc 다음에 나오는 토큰을 limiter로 설정한다.
 * @param meta 
 * @return int 성공 시 0, 실패 시 1
 */
int	modify_arg_to_limiter(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;

	token_num = meta->size;
	node = meta->head;
	while (token_num--)
	{
		if (!node)
			return (print_error(UNEXPECTED, 0));
		if (token_num && node->type == I_HRDOC)
			node->next->type = LIMITER;
		node = node->next;
	}
	return (0);
}
