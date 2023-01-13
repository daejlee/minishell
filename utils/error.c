/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:57:38 by hkong             #+#    #+#             */
/*   Updated: 2023/01/13 15:14:10 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	print_error(enum e_error_code error_code, char *str)
{
	printf("minishell: ");
	if (error_code == MALLOC_FAIL)
	{
		printf("memory allocation fails\n");
		exit(1);
	}
	else if (error_code == SYNTAX_ERROR)
		printf("syntax error near unexpected token \'%s\'\n", str);
	else if (error_code == AMBIGUOUS_REDIR)
		printf ("%s: ambiguous redirect\n", str);
	else if (error_code == UNEXPECTED)
	{
		printf ("unexpected behavior\n");
		exit(1);
	}
	return (1);
}

/**
 * @brief 
 * 따옴표의 짝이 맞지 않는 경우, syntax error를 출력합니다.
 * @param str 
 * @param end 
 * @return int 1
 */
int	quote_syntax_error(char *str, size_t end)
{
	char	*error_str;

	error_str = ft_substr(str, end, ft_strlen(str) - end);
	if (!error_str)
		return (print_error(MALLOC_FAIL, 0));
	print_error(SYNTAX_ERROR, error_str);
	free(error_str);
	return (1);
}
