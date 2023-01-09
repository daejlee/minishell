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
	//malloc leak
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
	idx = 'A';
	i = 0;
	while (idx <= 'Z')
	{
		if (temp->key[0] == idx)
			arr[i++] = temp;
		temp = temp->next;
		while (temp != head)
		{
			if (temp->key[0] == idx)
				arr[i++] = temp;
			temp = temp->next;
		}
		idx++;
	}
	idx = 'a';
	while (idx <= 'z')
	{
		if (temp->key[0] == idx)
			arr[i++] = temp;
		temp = temp->next;
		while (temp != head)
		{
			if (temp->key[0] == idx)
				arr[i++] = temp;
			temp = temp->next;
		}
		idx++;
	}
	i = 0;
	while (i < size - 2)
	{
		write(1, "declare -x ", 12);
		write(1, arr[i]->key, ft_strlen(arr[i]->key));
		write(1, "=\"", 3);
		write(1, arr[i]->value, ft_strlen(arr[i]->value));
		write(1, "\"\n", 3);
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
	// export만
	char	**temp;
	t_env	*env_temp;

	if (!name)
		return (print_sorted_env(env));
	temp = ft_split_modified(name);
	env_temp = find_env(env, temp[0]);
	if (env_temp && env_temp->value)
		env_temp->value = temp[1];
	else
	{
		env_temp = init_env(temp[0], temp[1]);
		push_env(&env, env_temp);
	}
	//예외처리
	return (0);
}
