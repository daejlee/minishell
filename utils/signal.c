/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:03:38 by hkong             #+#    #+#             */
/*   Updated: 2023/01/13 14:53:11 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	signal_default(void)
{
	signal(SIGINT, sig_main_process);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_execute(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_heredoc(void)
{
	signal(SIGINT, sig_heredoc_process);
	signal(SIGQUIT, SIG_IGN);
}
