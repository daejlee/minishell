/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:32:43 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/10 13:32:47 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	exec_built_in_seg(int built_in_code, char **com, t_env *env, int i)
{
	if (built_in_code == B_ECHO)
		return (exec_ft_echo(com));
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
}

int	exec_built_in(char **com, t_env *env)
{
	int	ret;
	int	built_in_code;

	built_in_code = is_built_in(com[0]);
	exec_built_in_seg(built_in_code, com, env, 1);
	return (ret);
}
