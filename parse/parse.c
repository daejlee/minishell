/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:22:23 by hkong             #+#    #+#             */
/*   Updated: 2022/12/30 19:49:18 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief 
 * parsing 메인 함수
 * @param env 환경 변수 리스트
 * @param str 들어온 목록
 * @return t_token_meta* 쪼개진 최종 토큰 값이 들어있다.
 */
t_token_meta	*parse(t_env *env, char *str)
{
	t_token_meta	*result;
	t_token			*node;

	//? 들어오는 인자가 NULL일 때 / 빈 문자열일 때 확인.
	result = init_token_meta();
	split_spaces_in_substr(result, str);
	interpret_quotes(result, env);
	split_operator(result);
	interpret_env(result, env);
	split_spaces(result, env);
	modify_init_to_arg(result);
	union_args_to_one(result);
	delete_space_token(result);
	return (result);
}
