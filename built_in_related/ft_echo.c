#include "../minishell.h"

/**
 * @brief 
 * 빌트인 echo 함수입니다. -n 옵션을 지원합니다.
 * original : echo [-n] [string ...]
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_echo(char *buf, int n_option)
{
	char	*printing_buf;

	if (n_option)
		printing_buf = ft_strjoin(buf, "");
	else
		printing_buf = ft_strjoin(buf, "\n");
	if (!printing_buf)
		return (-1);
	write(1, printing_buf, ft_strlen(printing_buf));
	return (0);
}