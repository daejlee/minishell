/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:30:30 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 14:58:50 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static char	**ft_split_modified(char *name)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * 2);
	if (!ret)
		return (NULL);
	i = 0;
	while (name[i] != '=')
		i++;
	ret[0] = (char *)malloc(sizeof(char) * (i + 1));
	ret[1] = (char *)malloc(sizeof(char) * (ft_strlen(name) - i));
	ft_strlcpy(ret[0], name, i + 1);
	ft_strlcpy(ret[1], name + i + 1, ft_strlen(name) - i);
	return (ret);
}

static void	seg(char *name, t_env *env)
{
	char	**temp;
	t_env	*env_temp;

	temp = ft_split_modified(name);
	env_temp = find_env(env, temp[0]);
	if (env_temp && env_temp->value)
	{
		free(env_temp->value);
		env_temp->value = temp[1];
		free(temp[0]);
	}
	else
		push_env(&env, init_env(temp[0], temp[1]));
	free(temp);
}

/**
 * @brief 
 * 빌트인 export 함수입니다. 옵션을 지원하지 않습니다.
 * original : export name[=word]...
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_export(char *name, t_env *env)
{
	t_env	*env_temp;

	if (!name)
		return (print_sorted_env(env));
	if (!ft_strchr(name, '='))
	{
		env_temp = find_env(env, name);
		if (!env_temp)
		{
			env_temp = init_env(ft_strdup(name), "");
			env_temp->value = NULL;
			push_env(&env, env_temp);
		}
		return (0);
	}
	seg(name, env);
	return (0);
}
