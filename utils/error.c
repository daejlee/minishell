/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:57:38 by hkong             #+#    #+#             */
/*   Updated: 2022/12/21 21:06:46 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(enum e_error_code error_code, char c)
{
	printf("minishell: ");
	if (error_code == MALLOC_FAIL)
		printf("memory allocation fails\n");
	else if (error_code == SYNTAX_ERROR)
		printf("syntax error near unexpected token %c", c);
	return (1);
}
