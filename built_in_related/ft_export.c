#include "minishell.h"

static char *ft_split_modified(char *name)
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

static int	print_sorted_env(t_env *env)
{
	int	size;
	int i;
	int	k;
	char	idx;
	unsigned int	len;
	t_env	*head;
	t_env	*temp;
	t_env	**arr;

	size = 1;
	head = env;
	temp = head->next;
	while (temp != head)
	{
		size++;
		temp = temp->next;
	}
	arr = (t_env **)malloc(sizeof(t_env *) * size);
	if (!arr)
		return (1);
	i = 0;
	temp = head;
	while (i < size)
	{
		arr[i++] = temp;
		temp = temp->next;
	}
	k = 0;
	while (k < size)
	{
		i = 0;
		while (i < size - 1)
		{
			if (ft_strlen(arr[i]->key) <= ft_strlen(arr[i + 1]->key))
				len = ft_strlen(arr[i + 1]->key);
			else
				len = ft_strlen(arr[i]->key);
			if (ft_strncmp(arr[i]->key, arr[i + 1]->key, len) > 0)
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
			i++;
		}
		k++;
	}
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(arr[i]->key, "_", ft_strlen(arr[i]->key)))
		{
			write(1, "declare -x ", 12);
			write(1, arr[i]->key, ft_strlen(arr[i]->key));
			if (arr[i]->value)
			{
				write(1, "=\"", 3);
				write(1, arr[i]->value, ft_strlen(arr[i]->value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
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
		env_temp = NULL;
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
	{
		env_temp = init_env(temp[0], temp[1]);
		push_env(&env, env_temp);
	}
	return (0);
}
