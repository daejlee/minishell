/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:57:23 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 16:52:17 by hkong            ###   ########.fr       */
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
		g_exit_status = 1;
	}
}

void	sig_excute_process(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		exit(131);
	}
}

void	sig_heredoc_process(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(1);
	}
}