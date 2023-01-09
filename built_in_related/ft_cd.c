#include "minishell.h"

static char	*ft_strjoin_modified(char const *s1, char const *s2)
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
	res[i] = '/';
	i = 0;
	while (s2[i])
	{
		res[s1_len + 1 + i] = s2[i];
		i++;
	}
	res[s1_len + 1 + i] = '\0';
	return (res);
}

static int	check_cdpath(char **curpath_adr, char *env_cdpath)
{
	char	**splitted_cdpath;
	char	*temp;
	int		i;

	if (!env_cdpath || env_cdpath[0] == '\0')
		return (1);
	else
		splitted_cdpath = ft_split(env_cdpath, ':');
	if (!splitted_cdpath)
		return (-1);
	i = 0;
	while (splitted_cdpath[i])
	{
		temp = splitted_cdpath[i];
		if (temp[ft_strlen(temp)] != '/')
			temp = ft_strjoin_modified(env_cdpath, temp);
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
			//free_arr(splitted_cdpath);
			return (0);
		}
	}
	//free_arr(splitted_cdpath);
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

static char	*get_env_val(char *key, t_env *env)
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

/**
 * @brief 
 * 빌트인 cd 함수입니다. 상대 경로 혹은 절대 경로만을 사용합니다. 옵션을 지원하지 않습니다.
 * original : cd [-L|-P] [directory]
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_cd(char *dir, t_env *env)
{
	char	*curpath;
	char	*temp_free;
	char	*env_home;
	char	*env_cdpath;
	char	*env_pwd;
	t_env	*node;
	int		ret;

	env_home = get_env_val("HOME", env);
	env_cdpath = get_env_val("CDPATH", env);
	env_pwd = get_env_val("PWD", env);
	node = find_env(env, "OLDPWD");
	if (node)
		(*node).value = env_pwd;
	if (!dir && (!env_home || env_home[0] == '\0'))
		return (1);
	else if (!dir)
		dir = env_home;
	if (dir[0] == '/')
		curpath = ft_strdup(dir);
	else
	{
		if (!ft_strncmp(dir, "..", 2) || dir[0] == '.' || check_cdpath(&curpath, env_cdpath))	//4th, 5th
			curpath = ft_strdup(dir);
	}
	if (!curpath)
		return (-1);
	if (curpath[0] != '/')
	{
		temp_free = curpath;
		if (env_pwd[ft_strlen(env_pwd) - 1] != '/')
			curpath = ft_strjoin_modified(env_pwd, curpath);
		else
			curpath = ft_strjoin(env_pwd, curpath);
		free(temp_free);
		if (!curpath)
			return (-1);
	}
	if (!curpath)
		return (-1);
	ret = chdir(curpath);
	node = find_env(env, "PWD");
	(*node).value = getcwd(NULL, 0);
	if (ret)
	{
		write(2, "ft_cd: no such file or directory: ", 35);
		write(2, dir, ft_strlen(dir));
		write(2, "\n", 1);
	}
	return (ret);
}
