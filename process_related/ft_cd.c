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


/*
5. 콜론으로 구분된 `CDPATH`에서 첫 경로명부터 시작한다. 경로명이 널이 아닐 때, 경로명이 /로 끝나지 않았다면 그 경로명, /, `directory`피연산자를 연결한 문자열이 디렉토리를 명시하는지 시험하라.
경로명이 널일 때, `./피연산자`가 디렉토리를 명시하는 지 시험하라. 둘 중 결과가 되는 문자열이 존재하면, `curpath`를 그 문자열로 설정하고 7번으로 진행된다.
그렇지 않을 때는 이 단계를 `CDPATH`의 경로명이 바닥날 때 까지 다음 경로명으로 넘어가며 반복하라.
*/
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

/*	빌트인 cd 함수입니다. 상대 경로 혹은 절대 경로만을 사용합니다.
	original : cd [-L|-P] [directory]	*/
int	ft_cd(char *dir, char *env_home, char *env_cdpath, char *env_pwd)
{
	char	*curpath;

	if (!dir && (!env_home || env_home[0] == '\0'))	//1st
		return (0);
	else if (!dir)	//2nd
		dir = env_home;
	if (dir[0] == '/')	//3rd
		curpath = dir;
	else
	{
		if (!ft_strncmp(dir, "..", 2) || dir[0] == '.' || check_cdpath(&curpath, env_cdpath))	//4th, 5th
			curpath = dir;
	}
	if (curpath[0] != '/')	//7th
	{
		if (env_pwd[ft_strlen(env_pwd)] != '/')
			curpath = ft_strjoin_modified(env_pwd, curpath);
		else
			curpath = ft_strjoin(env_pwd, curpath);
	}
	get_canonical_curpath();	//8th
	trim_curpath(&curpath);	//9th
	return (chdir(curpath));	//10th
}
