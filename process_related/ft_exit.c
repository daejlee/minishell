#include "../minishell.h"

/*	빌트인 exit 함수입니다. 옵션을 지원하지 않습니다.
	original : exit [n]	*/
int	ft_exit(void)
{
	exit(g_exit_status);
}
