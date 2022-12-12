#include "../minishell.h"

char	*ft_strjoin_modified(char const *s1, char const *s2)
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
			free_arr(splitted_cdpath);
			return (0);
		}
	}
	free_arr(splitted_cdpath);
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

static char	*delete_dot_slash(char *curpath)
{
	char	*temp;
	int		i;
	int		k;

	i = 0;
	while (ft_strnstr(curpath, "./", ft_strlen(curpath)))
	{
		temp = ft_strnstr(curpath, "./", 2);
		*temp = ' ';
		*(temp + 1) = ' ';
		i += 2;
	}
	temp = (char *)malloc(ft_strlen(curpath) - i);
	if (!temp)
	{
		free(curpath);
		return (NULL);
	}
	i = 0;
	k = 0;
	while (k < ft_strlen(curpath))
	{
		if (curpath[i] != ' ')
		{
			temp[i] = curpath[k];
			i++;
		}
		k++;
	}
	free(curpath);
	return (temp);
}

static char	*get_p_comp(char *curpath)
{
	char	*dot_dot_adr;
	char	*ret;
	int		i;

	dot_dot_adr = ft_strnstr(curpath, "..", ft_strlen(curpath));
	if (curpath == dot_dot_adr)
		return (dot_dot_adr);
	dot_dot_adr -= 3;
	i = 0;
	while (*(dot_dot_adr - i) != '/')
		i++;
	i--;
	ret = ft_substr((dot_dot_adr - i), 0, i);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*process_dot_dots(char *curpath)
{
	char	*p_comp;
	char	*temp;

	while (ft_strnstr(curpath, "..", ft_strlen(curpath)))
	{
		p_comp = get_p_comp(curpath);
		if (!p_comp)
			return (NULL);
		else if (p_comp == curpath)
			curpath += 3;
		else if (p_comp[0] != '/' || p_comp[0] != '.' || p_comp[1] == '.')
		{
			temp = ft_strdup(curpath);
			if (!temp)
				return (NULL);
			*(ft_strnstr(temp, "..", ft_strlen(temp)) - 1) = '\0';
			if (!opendir(temp))
			{
				free(temp);
				return (NULL);
			}
			free(temp);
		}
		else
			curpath = ft_strnstr(curpath, "..", ft_strlen(curpath)) + 2;
	}
}

static char	*trim_ret(char *curpath)
{
	char	*ret;
	char	*start_adr;
	int		i;
	int		k;

	i = 0;
	while (ft_strnstr(curpath, "//", ft_strlen(curpath)))
	{
		start_adr = ft_strnstr(curpath, "//", ft_strlen(curpath)) + 1;
		while (*(start_adr + i) == '/')
		{
			*(start_adr + i) = ' ';
			i++;
		}
	}
	ret = (char *)malloc(ft_strlen(curpath) - i);
	if (!ret)
	{
		free(curpath);
		return (NULL);
	}
	i = 0;
	k = 0;
	while (k < ft_strlen(curpath))
	{
		if (curpath[k] != ' ')
		{
			ret[i] = curpath[k];
			i++;
		}
		k++;
	}
	free(curpath);
	return (ret);
}

static char	*get_canonical_curpath(char *curpath)
{
	char	*ret;
	char	*free_temp;

	ret = delete_dot_slash(curpath);	//a
	if (!ret)
	{
		free(curpath);
		return (NULL);
	}
	free_temp = ret;
	ret = process_dot_dots(ret);	//b
	if (!ret)
	{
		free(free_temp);
		free(curpath);
		return (NULL);
	}
	free_temp = ret;
	ret = trim_ret(ret);	//c
	if (!ret)
	{
		free(free_temp);
		free(curpath);
	}
	return (ret);
}

/**
 * @brief 
 * 빌트인 cd 함수입니다. 상대 경로 혹은 절대 경로만을 사용합니다. 옵션을 지원하지 않습니다.
 * original : cd [-L|-P] [directory]
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_cd(char *dir, char *env_home, char *env_cdpath, char *env_pwd)
{
	char	*curpath;
	char	*temp_free;

	if (!dir && (!env_home || env_home[0] == '\0'))	//1st
		return (1);
	else if (!dir)	//2nd
		dir = env_home;
	if (dir[0] == '/')	//3rd
		curpath = ft_strdup(dir);
	else
	{
		if (!ft_strncmp(dir, "..", 2) || dir[0] == '.' || check_cdpath(&curpath, env_cdpath))	//4th, 5th
			curpath = ft_strdup(dir);
	}
	if (!curpath)
		return (-1);
	if (curpath[0] != '/')	//7th
	{
		temp_free = curpath;
		if (env_pwd[ft_strlen(env_pwd)] != '/')
			curpath = ft_strjoin_modified(env_pwd, curpath);
		else
			curpath = ft_strjoin(env_pwd, curpath);
		free(temp_free);
		if (!curpath)
			return (-1);
	}
	curpath = get_canonical_curpath(curpath);	//8th
	if (!curpath)
		return (-1);
	//trim_max_length(&curpath);	//9th, after implement PWD
	return (chdir(curpath));	//10th
}
