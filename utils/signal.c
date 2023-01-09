/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:03:38 by hkong             #+#    #+#             */
/*   Updated: 2023/01/09 22:26:39 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_default(void)
{
	signal(SIGINT, signal_process);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_execute(void)
{
	struct sigaction action;

	action.sa_handler = test1;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_process(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

//!heredoc SIGINT일 때 quit하기.
//!quit, enter 안먹히는 거 체크하기

void	test1(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
	}
}