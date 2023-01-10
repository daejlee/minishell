/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:30:30 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/10 17:26:19 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_ft_export
{
	t_env			*head;
	t_env			*temp;
	t_env			**arr;
	int				size;
	int				i;
	int				k;
	unsigned int	len;
}	t_ft_export;

static char	*ft_split_modified(char *name)
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

static int	seg_1(t_ft_export *p, t_env *env)
{
	int	i;

	p->size = 1;
	p->head = env;
	p->temp = p->head->next;
	while (p->temp != p->head)
	{
		p->size++;
		p->temp = p->temp->next;
	}
	p->arr = (t_env **)malloc(sizeof(t_env *) * p->size);
	if (!p->arr)
		return (1);
	i = 0;
	p->temp = p->head;
	while (i < p->size)
	{
		p->arr[i++] = p->temp;
		p->temp = p->temp->next;
	}
	return (0);
}

static int	seg_2(t_ft_export p)
{
	int	i;

	i = 0;
	while (i < p.size)
	{
		if (ft_strncmp(p.arr[i]->key, "_", ft_strlen(p.arr[i]->key)))
		{
			write(1, "declare -x ", 12);
			write(1, p.arr[i]->key, ft_strlen(p.arr[i]->key));
			if (p.arr[i]->value)
			{
				write(1, "=\"", 3);
				write(1, p.arr[i]->value, ft_strlen(p.arr[i]->value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}

static int	print_sorted_env(t_env *env)
{
	t_ft_export		p;

	if (seg(&p, env))
		return (1);
	p.k = 0;
	while (p.k < p.size)
	{
		p.i = 0;
		while (p.i < p.size - 1)
		{
			if (ft_strlen(p.arr[p.i]->key) <= ft_strlen(p.arr[p.i + 1]->key))
				p.len = ft_strlen(p.arr[p.i + 1]->key);
			else
				p.len = ft_strlen(p.arr[p.i]->key);
			if (ft_strncmp(p.arr[p.i]->key, p.arr[p.i + 1]->key, p.len) > 0)
			{
				p.temp = p.arr[p.i];
				p.arr[p.i] = p.arr[p.i + 1];
				p.arr[p.i + 1] = p.temp;
			}
			p.i++;
		}
		p.k++;
	}
	return (seg_2(p));
}

/**
 * @brief 
 * 빌트인 export 함수입니다. 옵션을 지원하지 않습니다.
 * original : export name[=word]...
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_export(char *name, t_env *env)
{
	char	**temp;
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
	temp = ft_split_modified(name);
	env_temp = find_env(env, temp[0]);
	if (env_temp && env_temp->value)
		env_temp->value = temp[1];
	else
		push_env(&env, init_env(temp[0], temp[1]));
	return (0);
}
