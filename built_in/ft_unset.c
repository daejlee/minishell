/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:26:33 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 12:55:08 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/**
 * @brief 
 * 빌트인 unset 함수입니다. 옵션을 지원하지 않습니다.
 * original : unset [-fv] name...
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_unset(char *name, t_env *env)
{
	if (delete_env(env, name))
		return (-1);
	return (0);
}
