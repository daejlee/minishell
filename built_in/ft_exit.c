/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:25:01 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 18:08:07 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/**
 * @brief 
 * 빌트인 exit 함수입니다. 옵션을 지원하지 않습니다.
 * original : exit [n]
 * @return int exit_status
 */
int	ft_exit(char **com)
{
	int	num;

	printf("exit\n");
	if (!com[0])
		exit (0);
	if (com[1])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (!is_number(com[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n", com[0]);
		exit(255);
	}
	num = ft_atoi(com[0]);
	num &= 255;
	exit(num);
}
