/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:22:18 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/10 20:09:26 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
}

char	*ft_strjoin_modified(char const *s1, char const *s2, char c)
{
	int				i;
	unsigned int	s1_len;
	char			*res;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 2));
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	i = 0;
	while (s2[i])
	{
		res[s1_len + 1 + i] = s2[i];
		i++;
	}
	res[s1_len + 1 + i] = '\0';
	return (res);
}

static int	seg(char **curpath_adr, char *env_cdpath, char **splitted_cdpath)
{
	int		i;
	char	*temp;

	i = 0;
	while (splitted_cdpath[i])
	{
		temp = splitted_cdpath[i];
		if (temp[ft_strlen(temp)] != '/')
			temp = ft_strjoin_modified(env_cdpath, temp, '/');
		else
			temp = ft_strjoin(env_cdpath, temp);
		if (!opendir(temp))
		{
			free(temp);
			i++;
		}
		else
		{
			*curpath_adr = temp;
			free_arr(splitted_cdpath);
			return (1);
		}
	}
	free_arr(splitted_cdpath);
	return (0);
}

int	check_cdpath(char **curpath_adr, char *env_cdpath)
{
	char	**splitted_cdpath;
	char	*temp;

	if (!env_cdpath || env_cdpath[0] == '\0')
		return (1);
	else
		splitted_cdpath = ft_split(env_cdpath, ':');
	if (!splitted_cdpath)
		return (-1);
	if (seg(curpath_adr, env_cdpath, splitted_cdpath))
		return (0);
	temp = ft_strjoin("./", *curpath_adr);
	if (opendir(temp))
	{
		*curpath_adr = temp;
		return (0);
	}
	else
	{
		free(temp);
		return (1);
	}
}

char	*get_env_val(char *key, t_env *env)
{
	t_env	*now;

	now = env;
	if (!ft_strncmp((now->key), key, ft_strlen(key) + 1))
		return (now->value);
	now = now->next;
	while (now != env)
	{
		if (!ft_strncmp((now->key), key, ft_strlen(key) + 1))
			return (now->value);
		now = now->next;
	}
	return (NULL);
}
