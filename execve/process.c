/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:19:29 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/11 12:56:04 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

int	get_pcs(t_token_meta *meta, t_env *env, char **envp)
{
	t_pcs	p;
	t_token	*now;

	init_p(&p);
	p.envp = envp;
	if (here_doc(meta, &p))
		return (1);
	terminal_set_echo();
	return (exec_fork(&p, meta, env));
}
