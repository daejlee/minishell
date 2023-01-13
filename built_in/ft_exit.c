/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:25:01 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 17:08:13 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/**
 * @brief 
 * 빌트인 exit 함수입니다. 옵션을 지원하지 않습니다.
 * original : exit [n]
 * @return int exit_status
 */
int	ft_exit(int num)
{
	while (num < 0)
		num += 256;
	while (num > 255)
		num -= 256;
	exit(num);
}
