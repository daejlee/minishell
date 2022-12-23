/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:41:15 by hkong             #+#    #+#             */
/*   Updated: 2022/12/23 20:31:17 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief 
 * token의 노드를 초기화하는 함수입니다.
 * @param str 토큰 문자열
 * @return t_token* 실패 시 NULL
 */
t_token	*init_token(char *str, enum e_token_type type)
{
	t_token	*token;

	if (!str)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		free(str);
		return (NULL);
	}
	token->original_str = str;
	token->str = ft_strdup(str);
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	if (!token->str)
	{
		free(str);
		free(token);
		return (NULL);
	}
	return (token);
}

/**
 * @brief 
 * queue 형태인 token 리스트의 제일 끝에 노드를 삽입하는 함수입니다.
 * @param meta t_token_meta
 * @param node 삽입할 노드
 * @return int 성공 시 0, 실패 시 1
 */
int	push_token(t_token_meta *meta, t_token *node)
{
	t_token	*head;

	if (!node || !meta)
		return (1);
	if (!meta->size)
	{
		meta->head = node;
		node->next = node;
		node->prev = node;
	}
	else
	{
		head = meta->head;
		node->next = head;
		node->prev = head->prev;
		head->prev->next = node;
		head->prev = node;
	}
	meta->size++;
	return (0);
}

/**
 * @brief 
 * queue 형태인 token 리스트의 제일 앞에 있는 노드를 return하는 함수입니다.
 * @param meta t_token_meta
 * @return t_token* 비어있을 시 NULL
 */
t_token	*pop_token(t_token_meta *meta)
{
	t_token	*node;

	if (!meta || !meta->size)
		return (NULL);
	node = meta->head;
	if (meta->size == 1)
		meta->head = NULL;
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		meta->head = node->next;
	}
	node->next = NULL;
	node->prev = NULL;
	meta->size--;
	return (node);
}

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		if (token->original_str)
			free(token->original_str);
		token->prev = NULL;
		token->next = NULL;
		free(token);
	}
}
