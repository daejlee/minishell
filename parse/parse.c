/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:22:23 by hkong             #+#    #+#             */
/*   Updated: 2022/12/16 15:28:51 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	interprete_quotes(t_token_meta *meta, char *str, t_env *env);
int	change_key_to_value(char **str, char *value, size_t start, size_t end);
void	free_multiple_str(char *str1, char *str2, char *str3, char *str4);

t_token_meta	*parse(t_env *env, char *str)
{
	t_token_meta	*result;
	t_token			*node;

	result = init_token_meta();
	interprete_quotes(result, str, env);
	return (result);
}

int	interprete_quotes(t_token_meta *meta, char *str, t_env *env)
{
	char	*tmp;
	size_t	start;
	size_t	end;

	start = 0;
	while (str[start] && str[start] == '\'' && str[start] == '\"')
		start++;
	if (!str[start])
		return (push_token(meta, init_token(str)));
	end = start + 1;
	if (str[start] == '\'')
	{
		while (str[end] && str[end] != '\'')
			end++;
		if (!str[end])
			return (push_token(meta, init_token(str)));
		if (start)
			push_token(meta, init_token(ft_substr(str, start, start)));
		if (end - start - 1)
			push_token(meta, init_token(ft_substr(str, start + 1, end - start - 1)));
		interprete_quotes(meta, ft_substr(str, end + 1, ft_strlen(str) - end - 1), env);
		free(str);
	}
	else
	{
		while (str[end] && str[end] != '\"')
			end++;
		if (!str[end])
			return (push_token(meta, init_token(str)));
		if (start)
			push_token(meta, init_token(ft_substr(str, start, start)));
		if (end - start - 1)
		{
			tmp = ft_substr(str, start + 1, end - start - 1);
			interprete_env(&tmp, env);
			push_token(meta, init_token(tmp));
		}
		interprete_quotes(meta, ft_substr(str, end + 1, ft_strlen(str) - end - 1), env);
		free(str);
	}
}

int	is_env_allowed_char(int is_first, char c)
{
	if (c == '_')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (!is_first && c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	interprete_env(char **str, t_env *env)
{
	size_t	start;
	size_t	end;
	char	*key;
	char	*value;
	t_env	*node;

	start = 0;
	while ((*str)[start])
	{
		if ((*str)[start] == '$')
		{
			end = start + 1;
			while ((*str)[end] && is_env_allowed_char(end == start + 1, (*str)[end]))
				end++;
			if (end == start + 1)
			{
				start++;
				continue ;
			}
			key = ft_substr(*str, start + 1, end - start - 1);
			//! null guard
			node = find_env(env, key);
			if (node)
				value = ft_strdup(node->value);
			else
				value = ft_strdup("");
			//! null guard
			change_key_to_value(str, value, start, end);
			//! error check
			start = end + ft_strlen(value) - ft_strlen(key);
			free_multiple_str(value, key, NULL, NULL);
		}
		start++;
	}
}

int	change_key_to_value(char **str, char *value, size_t start, size_t end)
{
	char	*result;
	char	*result_tmp;
	char	*front;
	char	*back;

	if (!value || !*str)
		return (1);
	front = ft_substr(*str, 0, start);
	back = ft_substr(*str, end, ft_strlen(*str) - end);
	result_tmp = ft_strjoin(front, value);
	result = ft_strjoin(result_tmp, back);
	if (!(front && back && result_tmp && result))
	{
		free_multiple_str(front, back, result_tmp, result);
		return (1);
	}
	free_multiple_str(front, back, result_tmp, *str);
	*str = result;
	return (0);
}
