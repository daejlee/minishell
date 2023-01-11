/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:32:43 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 13:31:16 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	exec_built_in_seg(int built_in_code, char **com, t_env *env, int i);

/**
 * @brief 
 * 각각의 built_in을 실행하고 리턴한다.
 * @param built_in_code enum 형태의 값
 * @return int 실행 이후 exit status
 */
static int	exec_built_in_seg(int built_in_code, char **com, t_env *env, int i)
{
	if (built_in_code == B_ECHO)
		return (ft_echo(com));
	else if (built_in_code == B_CD)
		return (ft_cd(com[1], env));
	else if (built_in_code == B_PWD)
		return (ft_pwd());
	else if (built_in_code == B_EXPORT)
	{
		if (!com[i])
			return (ft_export(NULL, env));
		while (com[i])
			ft_export(com[i++], env);
		return (0);
	}
	else if (built_in_code == B_UNSET)
	{
		while (com[i])
			built_in_code = ft_unset(com[i++], env);
		return (built_in_code);
	}
	else if (built_in_code == B_ENV)
		return (ft_env(env));
	else if (built_in_code == B_EXIT)
		return (ft_exit());
	return (0);
}

/**
 * @brief 
 * built_in의 메인 함수
 * @param com command 이차원 배열
 * @param env
 * @return int 실행 이후 exit status
 */
int	exec_built_in(char **com, t_env *env)
{
	int	built_in_code;

	//? command 및 env가 null이 아님이 확정되어있나? 
	built_in_code = is_built_in(com[0]);
	return (exec_built_in_seg(built_in_code, com, env, 1));
}
