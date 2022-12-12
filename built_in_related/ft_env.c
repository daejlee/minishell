#include "../minishell.h"

/**
 * @brief 
 * 빌트인 env 함수입니다. 옵션을 지원하지 않습니다.
 * original : env [-0iv] [-u name] [name=value ...]
 * @return int 성공 시 0
 */
int	ft_env(t_env *env)
{
	t_env	*head;
	t_env	*now;

	head = env;
	now = head;
	now = now->next;
	ft_printf("%s=%s\n", now->key, now->value);
	while (now != head)
	{
		ft_printf("%s=%s\n", now->key, now->value);
		now = now->next;
	}
	return (0);
}
