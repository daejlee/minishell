/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:03:38 by hkong             #+#    #+#             */
/*   Updated: 2023/01/10 15:40:04 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_default(void)
{
	fprintf(stderr, "default\n");
	signal(SIGINT, sig_main_process);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_execute(void)
{
	fprintf(stderr, "execute\n");
	signal(SIGINT, sig_excute_process);
	signal(SIGQUIT, sig_excute_process);
}

void	signal_ignore(void)
{
	fprintf(stderr, "ignore\n");
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	signal_heredoc(void)
{
	fprintf(stderr, "hrdoc\n");
	signal(SIGINT, sig_heredoc_process);
	signal(SIGINT, SIG_IGN);
}

void	sig_main_process(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

//!heredoc SIGINT일 때 quit하기.
//!quit, enter 안먹히는 거 체크하기

void	sig_excute_process(int sig)
{
	fprintf(stderr, "execute_process\n");
	if (sig == SIGINT)
		write(2, "\n", 1);
	if (sig == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}

void	sig_heredoc_process(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(1);
	}
}