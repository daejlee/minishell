/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:15:05 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 01:15:31 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "process.h"
#include "parse.h"

/* 시작 전 각종 초기화가 이뤄지는 부분 */
int	set_env(t_env **env, char **envp)
{
	int		i;
	char	**temp;
	t_env	*now;

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

int	main(int argc, char **argv, char **envp)
{
	char			*buf;
	t_token_meta	*meta;
	t_env			*env;

	set_env(&env, envp);
	meta = NULL;
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
			// t_token *node;
			// node = meta->head;
			// for (int i = 0; i < meta->size; i++)
			// {
			// 	printf("%s|%s|%d\n", node->str, node->origin_str, node->type);
			// 	node = node->next;
			// }
			g_exit_status = get_pcs(meta, env, envp);
			free_token_meta(meta);
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
	terminal_set_echo();
	return (0);
}
