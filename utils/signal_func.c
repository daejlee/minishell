/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:57:23 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 13:45:30 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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