/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:03:38 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 18:04:56 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	signal_default(void)
{
	// fprintf(stderr, "default %d\n", getpid());
	signal(SIGINT, sig_main_process);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_execute(void)
{
	// fprintf(stderr, "execute %d\n", getpid());
	signal(SIGINT, sig_excute_process);
	signal(SIGQUIT, sig_excute_process);
}

void	signal_ignore(void)
{
	// fprintf(stderr, "ignore %d\n", getpid());
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(void)
{
	// fprintf(stderr, "hrdoc %d\n", getpid());
	signal(SIGINT, sig_heredoc_process);
	signal(SIGQUIT, SIG_IGN);
}
