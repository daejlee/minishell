/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:28:19 by hkong             #+#    #+#             */
/*   Updated: 2022/12/23 20:31:53 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief 
 * queue 형태인 token의 head와 size를 갖는 token_meta를 초기화하는 함수입니다.
 * @return t_token_meta* 실패 시 NULL
 */
t_token_meta	*init_token_meta(void)
{
	t_token_meta	*meta;

	meta = (t_token_meta *)malloc(sizeof(t_token_meta));
	if (!meta)
		return (NULL);
	meta->size = 0;
	meta->head = NULL;
	return (meta);
}

/**
 * @brief 
 * token_meta와 token 리스트를 모두 free해주는 함수
 * @param meta 
 * @return t_token_meta* NULL
 */
t_token_meta	*free_token_meta(t_token_meta *meta)
{
	t_token	*node;

	if (meta)
	{
		while (meta->size)
		{
			node = pop_token(meta);
			if (node)
				free_token(node);
		}
		free(meta);
	}
	return (NULL);
}
