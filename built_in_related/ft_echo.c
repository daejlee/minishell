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
	res[i] = ' ';
	i = 0;
	while (s2[i])
	{
		res[s1_len + 1 + i] = s2[i];
		i++;
	}
	res[s1_len + 1 + i] = '\0';
	return (res);
}

int	get_n_option(char **com, int *n_flag_adr)
{
	int	i;
	int	k;

	i = 1;
	if (!ft_strncmp(com[0], "echo", 4))
	{
		while (!ft_strncmp(com[i], "-n", 2))
		{
			k = 2;
			while (com[i][k])
			{
				//echo -nnnkn -nnnnn a
				if (com[i][k] != 'n')
					return (i);
				k++;
			}
			*n_flag_adr = 1;
			i++;
		}
		if (i == 1)
		{
			*n_flag_adr = 0;
			return (0);
		}
		return (i);
	}
	else
	{
		if (!ft_strncmp(com[1], "-n", 3))
		{
			*n_flag_adr = 1;
			return (1);
		}
		*n_flag_adr = 0;
		return (0);
	}
}

char	*get_echo_buf(char **com, int n_option)
{
	char	*ret;
	char	*temp;
	int		i;
	int		fst_flag;

	fst_flag = 1;
	i = 1;
	if (n_option)
		i += (n_option - 1);
	ret = "";
	while (com[i])
	{
		temp = ret;
		if (!fst_flag)
		{
			ret = ft_strjoin_modified(ret, com[i]);
			//free(temp);
		}
		else
			ret = com[i];
		fst_flag = 0;
		i++;
	}
	return (ret);
}

int	exec_ft_echo(char **com)
{
	char	*buf;
	int		n_option;
	int		n_flag;

	if (!com[1])
		return (ft_echo("", 0));
	n_flag = 0;
	n_option = get_n_option(com, &n_flag);
	buf = get_echo_buf(com, n_option);
	if (!buf)
		return (-1);
	return (ft_echo(buf, n_flag));
}

/**
 * @brief 
 * 빌트인 echo 함수입니다. -n 옵션을 지원합니다.
 * original : echo [-n] [string ...]
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_echo(char *buf, int n_flag)
{
	char	*printing_buf;

	if (n_flag)
		printing_buf = ft_strjoin(buf, "");
	else
		printing_buf = ft_strjoin(buf, "\n");
	if (!printing_buf)
		return (-1);
	write(1, printing_buf, ft_strlen(printing_buf));
	return (0);
}