/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:22:18 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 13:18:09 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

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
