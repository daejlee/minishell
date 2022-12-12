#include "../minishell.h"

/**
 * @brief 
 * 빌트인 export 함수입니다. 옵션을 지원하지 않습니다.
 * original : export name[=word]...
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_export(char *name, t_env *env)
{
	char	**temp;
	t_env	*env_temp;

	temp = ft_split(name, '=');
	env_temp = init_env(temp[0], temp[1]);
	if (!temp || push_env(&env, &env_temp))
		return (-1);
	return (0);
}
