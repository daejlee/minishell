/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:24:50 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 12:54:50 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

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
	if (now->value)
		printf("%s=%s\n", now->key, now->value);
	now = now->next;
	while (now != head)
	{
		if (now->value)
			printf("%s=%s\n", now->key, now->value);
		now = now->next;
	}
	return (0);
}
