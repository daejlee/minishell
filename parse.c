/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:47:49 by hkong             #+#    #+#             */
/*   Updated: 2022/12/01 20:59:59 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 환경변수 포인터를 받아와 실행 경로를 추출하는 함수입니다. */
char	**get_sh_path(char **envp)
{
	unsigned int	i;
	char			**sh_paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			sh_paths = ft_split(envp[i], ':');
			if (!sh_paths)
				return (NULL);
			ft_strlcpy(sh_paths[0], sh_paths[0] + 5,
				ft_strlen(sh_paths[0]) - 4);
			return (sh_paths);
		}
		else
			i++;
	}
	return (NULL);
}

/**
 * @brief 
 * 링크드리스트인 token의 head와 size를 갖는 token_meta를 초기화하는 함수입니다.
 * @return t_token_meta* 
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
 * 
 * @param str 
 * @return t_token* 
 */
t_token	*init_token(char *str)
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
	token->str = str;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

int	push_back_token(t_token_meta *meta, t_token *node)
{
	t_token	*head;

	if (!node || !meta)
		return (1);
	head = meta->head;
	if (!head)
	{
		head = node;
		node->next = node;
		node->prev = node;
	}
	else
	{
		node->next = head;
		node->prev = head->prev;
		head->prev->next = node;
		head->prev = node;
	}
	meta->size++;
	return (0);
} 

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

int	is_white_space(char c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}

t_token_meta	*parse(char *str)
{
	t_token_meta	*result;
	size_t			start;
	size_t			end;

	result = init_token_meta();
	if (!result)
		return (NULL);
	start = 0;
	end = 0;
	while (str[end] || start != end)
	{
		if (is_white_space(str[end]) && start == end)
		{
			start++;
			end++;
		}
		else if (str[end] && !is_white_space(str[end]))
			end++;
		else
		{
			printf("%s\n",ft_substr(str, start, end - start));
			push_back_token(result, init_token(ft_substr(str, start, end - start)));
			start = end;
		}
	}
	return (result);
}

int main(int argc, char *argv[])
{
	t_token_meta	*meta;
	t_token	*node;

	argc = 0;
	meta = parse(argv[1]);
	node = pop_token(meta);
	while (node)
	{
		printf("%s\n", node->str);
		node = pop_token(meta);
	}
	return (0);
}

// int	check_substr_validate(t_stack *stk, char *str)
// {
// 	size_t	count;
// 	size_t	start;
// 	size_t	end;

// 	count = 0;
// 	start = 0;
// 	end = 0;
// 	while (str[end] || start != end)
// 	{
// 		if (str[end] == ' ' && start == end)
// 		{
// 			start++;
// 			end++;
// 		}
// 		else if (str[end] && str[end] != ' ')
// 			end++;
// 		else
// 		{
// 			if (!check_number_validate(stk, ft_substr(str, start, end - start)))
// 				return (0);
// 			start = end;
// 			count++;
// 		}
// 	}
// 	return (count);
// }
