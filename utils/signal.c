/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:03:38 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 13:01:44 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	signal_default(void)
{
	// fprintf(stderr, "default\n");
	signal(SIGINT, sig_main_process);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_execute(void)
{
	// fprintf(stderr, "execute\n");
	signal(SIGQUIT, sig_excute_process);
	signal(SIGINT, sig_excute_process);
}

void	signal_ignore(void)
{
	// fprintf(stderr, "ignore\n");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(void)
{
	// fprintf(stderr, "hrdoc\n");
	signal(SIGINT, sig_heredoc_process);
	signal(SIGQUIT, SIG_IGN);
}
