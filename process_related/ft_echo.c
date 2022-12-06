#include "../minishell.h"

/*	빌트인 echo 함수입니다. -n 옵션을 지원합니다.
	original : echo [-n] [string ...]	*/
int	ft_echo(char *buf, int n_option)
{
	int		write_ret;
	char	*printing_buf;

	if (n_option)
		printing_buf = ft_strjoin(buf, "");
	else
		printing_buf = ft_strjoin(buf, "\n");
	if (!printing_buf)
		return (1);
	write_ret = write(1, printing_buf, ft_strlen(printing_buf));
	free(printing_buf);
	if (write_ret == -1)
		return (1);
	else
		return (0);
}