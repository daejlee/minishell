/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:47:49 by hkong             #+#    #+#             */
/*   Updated: 2022/12/12 21:23:26 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_meta	*old_parse(char *str)
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
		if (str[end] && is_white_space(str[end]) && start == end)
			set_start_end(&start, &end, start + 1, end + 1);
		else if (str[end] && !is_white_space(str[end]))
			set_start_end(NULL, &end, start, end + 1);
		else
		{
			if (push_token(result, \
					lexical_analyzer(ft_substr(str, start, end - start))))
				return (free_token_meta(result));
			set_start_end(&start, NULL, end, end);
		}
	}
	return (result);
}

t_token	*old_lexical_analyzer(char *str)
{
	t_token	*token;

	token = init_token(str);
	if (!token)
		return (NULL);
	if (ft_strlen(str) == 1 && !ft_strncmp(str, "|", 1))
		token->type = PIPE;
	else if (ft_strlen(str) == 1 && !ft_strncmp(str, "<", 1))
		token->type = I_REDIR;
	else if (ft_strlen(str) == 1 && !ft_strncmp(str, ">", 1))
		token->type = O_REDIR;
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, "<<", 2))
		token->type = I_HRDOC;
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, ">>", 2))
		token->type = O_APPND;
	return (token);
}

void	old_set_start_end(size_t *start, size_t *end, \
							size_t start_num, size_t end_num)
{
	if (start)
		*start = start_num;
	if (end)
		*end = end_num;
}

// int	main(int argc, char *argv[])
// {
// 	t_token_meta	*meta;
// 	t_token			*node;

// 	printf("%d\n",argc);
// 	meta = parse(argv[1]);
// 	node = pop_token(meta);
// 	while (node)
// 	{
// 		printf("%s %d\n", node->str, node->type);
// 		node = pop_token(meta);
// 	}
// 	return (0);
// }
