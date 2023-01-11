/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:44:56 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 13:01:48 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	terminal_unset_echo(void)
{
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminal);
}

void	terminal_set_echo(void)
{
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &terminal);
}
