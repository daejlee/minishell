/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:15:05 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 18:21:19 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "process.h"
#include "parse.h"
#include "utils.h"

/* 시작 전 각종 초기화가 이뤄지는 부분 */
int	set_env(t_env **env, char **envp)
{
	int		i;
	char	**temp;

	*env = NULL;
	i = 0;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (!temp)
			return (print_error(MALLOC_FAIL, 0));
		if (push_env(env, init_env(temp[0], temp[1])))
			return (print_error(MALLOC_FAIL, 0));
		free(temp);
		i++;
	}
	return (0);
}

static void	do_minishell(t_env *env, char **envp)
{
	char			*buf;
	t_token_meta	*meta;

	while (1)
	{
		terminal_unset_echo();
		signal_default();
		buf = readline("minishell 0.1.3$ ");
		if (buf)
		{
			if (ft_strlen(buf))
				add_history(buf);
			meta = parse(env, buf);
			if (!meta)
				continue ;
			g_exit_status = get_pcs(meta, env, envp);
			free_token_meta(meta);
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	set_env(&env, envp);
	(void)argc;
	(void)argv;
	do_minishell(env, envp);
	terminal_set_echo();
	return (0);
}
