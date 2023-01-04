/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:23:23 by hkong             #+#    #+#             */
/*   Updated: 2023/01/02 22:09:45 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_init_to_arg(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;

	if (!meta)
		return ;
	token_num = meta->size;
	node = meta->head;
	while (token_num--)
	{
		if (node->type == INIT)
			node->type = ARG;
		node = node->next;
	}
}

//todo: empty도 합쳐야 함!!
int	union_args_to_one(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;
	char	*new_str;
	char	*new_origin_str;

	token_num = meta->size;
	while (token_num--)
	{
		node = pop_token(meta);
		printf("%d %d\n", (node->type == ARG || node->type == EMPTY), (node->next->type == ARG || node->next->type == EMPTY));
		if (token_num && (node->type == ARG || node->type == EMPTY) && (node->next->type == ARG || node->next->type == EMPTY))
		{
			new_str = ft_strdup(node->str);
			new_origin_str = ft_strdup(node->origin_str);
			while (token_num && (node->next->type == ARG || node->next->type == EMPTY))
			{
				free_token(node);
				if (!new_str || !new_origin_str)
					return (fail_and_free_multiple_str(new_str, new_origin_str, NULL, NULL));
				node = pop_token(meta);
				token_num--;
				new_str = ft_strjoin(new_str, node->str);
				new_origin_str = ft_strjoin(new_origin_str, node->origin_str);
			}
			free_token(node);
			if (!new_str || !new_origin_str)
				return (fail_and_free_multiple_str(new_str, new_origin_str, NULL, NULL));
			node = init_token(new_str, ARG);
			if (!node)
				return (fail_and_free_multiple_str(new_str, new_origin_str, NULL, NULL));
			set_token_origin(node, new_origin_str);
			push_token(meta, node);
		}
		else
			push_token(meta, node);
	}
}

int	delete_space_token(t_token_meta *meta)
{
	size_t	token_num;
	t_token	*node;

	token_num = meta->size;
	while (token_num--)
	{
		node = pop_token(meta);
		if (node->type == BLANK)
			free_token(node);
		else
			push_token(meta, node);
	}
	return (1);
}
