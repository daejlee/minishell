/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:24:23 by hkong             #+#    #+#             */
/*   Updated: 2022/12/16 21:37:52 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * str1과 str2가 길이&값이 완전히 같은지 확인하는 함수
 * @return int 같으면 1, 다르면 0
 */
int	is_exactly_same(char *str1, char *str2)
{
	if (!str1 ^ !str2)
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	if (ft_strncmp(str1, str2, ft_strlen(str1)))
		return (0);
	return (1);
}

/**
 * @brief 
 * char * 형태의 모든 문자열 인자가 NULL이 아닐 시 free해주는 함수
 * @return 0
 */
int	ok_and_free_multiple_str(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	if (str4)
		free(str4);
	return (0);
}

/**
 * @brief 
 * char * 형태의 모든 문자열 인자가 NULL이 아닐 시 free해주는 함수
 * @return 1
 */
int	fail_and_free_multiple_str(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	if (str4)
		free(str4);
	return (1);
}
