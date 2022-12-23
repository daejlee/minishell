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

#include "../minishell.h"

int	split_operator(t_token_meta *meta)
{
	t_token	*node;
	size_t	token_num;
	size_t	index;

	token_num = meta->size;
	while (token_num--)
	{
		node = pop_token(meta);
		index = operator_index(node->str);
		if (!index || node->type == ARG)
		{
			push_token(meta, node);
			continue ;
		}
		if (split_operator_in_substr(meta, node->str))
		{	
			free(node);
			return (print_error(MALLOC_FAIL, 0));
		}
		free(node);
	}
	return (0);
}

int	split_operator_in_substr(t_token_meta *meta, char *str)
{
	size_t	index;

	index = operator_index(str);
	if (!index)
	{
		if (push_token(meta, init_token(str, INIT)))
			return (fail_and_free_multiple_str(str, NULL, NULL, NULL));
		return (0);
	}
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
