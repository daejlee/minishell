/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:22:23 by hkong             #+#    #+#             */
/*   Updated: 2022/12/12 21:55:22 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_meta	*parse(char *str)
{
	t_token_meta	*result;

	result = init_token_meta();
	push_token(result, init_token(str));
	parse_interprete_quotes(result);
}

void	parse_interprete_quotes(t_token_meta *meta)
{
	t_token	*node;
	size_t	start;
	size_t	end;

	node = 
	while ()
}
