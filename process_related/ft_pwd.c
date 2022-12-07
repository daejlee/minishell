#include "../minishell.h"

/*	빌트인 pwd 함수입니다. 옵션을 지원하지 않습니다.
	original : pwd [-L | -P]	*/
int	ft_pwd(void)
{
	char	buf[PATH_MAX];
	char	*ret;

	ft_memset(buf, 0, PATH_MAX);
	ret = getcwd(buf, 1024);
	if (!ret)
		return (-1);
	write(1, buf, ft_strlen(buf));
	return (0);
}
