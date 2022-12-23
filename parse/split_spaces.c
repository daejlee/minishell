/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:16:44 by hkong             #+#    #+#             */
/*   Updated: 2022/12/22 21:46:52 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_quotes(char *str, size_t *end);
/*
int	split_spaces(t_token_meta *meta, char *str)
{
	size_t	start;
	size_t	end;
	size_t	single_quotes;
	size_t	double_quotes;

	initialize_numbers(&start, &end, &single_quotes, &double_quotes);
	while (str[end] || start != end)
	{
		if (str[end] && str[end] == ' ' && start == end)
			set_start_end(&start, &end, start + 1, end + 1);
		else if (str[end] && (str[end] != ' ' || \
								single_quotes % 2 || double_quotes % 2))
		{
			analyze_quotes(str[end], &single_quotes, &double_quotes);
			set_start_end(NULL, &end, start, end + 1);
		}
		else
		{
			if (push_token(meta, init_token(ft_substr(str, start, end - start), INIT)))
				return (1);
			set_start_end(&start, NULL, end, end);
		}
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		printf("error!\n");
	return (0);
}
*/

int	split_spaces(t_token_meta *meta, char *str)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (str[end] || start != end)
	{
		if (str[end] && str[end] == ' ' && start == end)
			set_start_end(&start, &end, start + 1, end + 1);
		else if (str[end] && str[end] != ' ')
		{
			if (skip_quotes(str, &end))
				return (print_error(SYNTAX_ERROR, str[end - 1]));
			set_start_end(NULL, &end, start, end + 1);
		}
		else
		{
			if (push_token(meta, init_token(ft_strdup(" "), BLANK)))
				return (print_error(MALLOC_FAIL, 0));
			if (push_token(meta, \
					init_token(ft_substr(str, start, end - start), INIT)))
				return (print_error(MALLOC_FAIL, 0));
			set_start_end(&start, NULL, end, end);
		}
	}
	return (0);
}

t_token	*old_lexical_analyzer(char *str)
{
	t_token	*token;

	token = init_token(str, INIT);
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

void	analyze_quotes(char c, size_t *single_quotes, size_t *double_quotes)
{
	if (c == '\'')
		(*single_quotes)++;
	else if (c == '\"')
		(*double_quotes)++;
	if ((*single_quotes && *single_quotes % 2 == 0) \
						|| (*double_quotes && *double_quotes % 2 == 0))
	{
		*single_quotes = 0;
		*double_quotes = 0;
	}
}

int	skip_quotes(char *str, size_t *end)
{
	if (str[*end] == '\'')
		while (str[++(*end)] && str[*end] != '\'')
			;
	if (str[*end] == '\"')
		while (str[++(*end)] && str[*end] != '\"')
			;
	if (!str[*end])
		return (1);
	return (0);
}