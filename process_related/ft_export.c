#include "../minishell.h"

/*	빌트인 export 함수입니다. 옵션을 지원하지 않습니다.
	original : export name[=word]...	*/
int	ft_export(char *name, t_env *env)
{
	char	**temp;

	temp = ft_split(name, '=');
	if (!temp || push_env(env, init_env(temp[1], temp[2])))
		return (1);
	return (0);
}
