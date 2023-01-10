/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:26:22 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/10 16:26:24 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * @brief 
 * 빌트인 pwd 함수입니다. 옵션을 지원하지 않습니다.
 * original : pwd [-L | -P]
 * @return int 성공 시 0, 실패 시 -1
 */
int	ft_pwd(void)
{
	char	buf[PATH_MAX];
	char	*ret;

	ft_memset(buf, 0, PATH_MAX);
	ret = getcwd(buf, 1024);
	if (!ret)
		return (-1);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}
