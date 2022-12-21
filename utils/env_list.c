/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:33:27 by hkong             #+#    #+#             */
/*   Updated: 2022/12/21 16:08:06 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief 
 * env 노드를 만드는 함수입니다.(key, value 필수)
 * @return t_env* key, value 둘 중 하나가 null이거나 malloc 실패 시 NULL반환
 */
t_env	*init_env(char *key, char *value)
{
	t_env	*result;

	if (!key)
	{
		if (value)
			free(value);
		return (NULL);
	}
	if (!value)
	{
		free(key);
		return (NULL);
	}
	result = (t_env *)malloc(sizeof(t_env));
	if (!result)
		return (NULL);
	result->key = key;
	result->value = value;
	result->next = NULL;
	result->prev = NULL;
	return (result);
}

/**
 * @brief 
 * t_env의 제일 끝에 노드를 삽입하는 함수
 * @return int 성공시 0, 실패시 1
 */
int	push_env(t_env **head, t_env **node)
{
	if (!*node)
		return (1);
	if (!*head)
	{
		*head = *node;
		(*head)->next = *head;
		(*head)->prev = *head;
		return (0);
	}
	(*node)->next = (*head);
	(*node)->prev = (*head)->prev;
	(*head)->prev->next = *node;
	(*head)->prev = *node;
	return (0);
}

/**
 * @brief 
 * 삭제 대신, key값을 가지는 t_env의 value를 NULL로 설정해주는 함수 
 * @return int 성공시 0, 실패시 1
 */
int	delete_env(t_env *head, char *key)
{
	t_env	*node;

	node = find_env(head, key);
	if (!node)
		return (1);
	node->value = NULL;
	return (0);
}

/**
 * @brief 
 * key값이 완전히 일치하는 t_env를 반환하는 함수
 * @param head t_env 리스트
 * @param key 찾는 key 값
 * @return t_env* 못찾으면 NULL
 */
t_env	*find_env(t_env *head, char *key)
{
	t_env	*node;
	size_t	key_len;

	if (!head || !key)
		return (NULL);
	node = head;
	if (is_exactly_same(node->key, key))
		return (node);
	node = node->next;
	while (!is_exactly_same(node->key, head->key))
	{
		if (is_exactly_same(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}
