/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:57:38 by hkong             #+#    #+#             */
/*   Updated: 2023/01/02 18:36:32 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(enum e_error_code error_code, char *str)
{
	printf("minishell: ");
	if (error_code == MALLOC_FAIL)
		printf("memory allocation fails\n");
	else if (error_code == SYNTAX_ERROR)
		printf("syntax error near unexpected token \'%s\'\n", str);
	else if (error_code == AMBIGUOUS_REDIR)
		printf ("%s: ambiguous redirect\n", str);
	else if (error_code == UNEXPECTED)
		printf ("unexpected behavior\n", str);
	return (1);
}
