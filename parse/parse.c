/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:22:23 by hkong             #+#    #+#             */
/*   Updated: 2023/01/02 21:27:54 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * parsing 메인 함수
 * @param env 환경 변수 리스트
 * @param str 들어온 목록
 * @return t_token_meta* 쪼개진 최종 토큰 값이 들어있다.
 */
t_token_meta	*parse(t_env *env, char *str)
{
	t_token_meta	*meta;
	t_token			*node;

	meta = init_token_meta();
	if (!meta)
	{
		print_error(MALLOC_FAIL, 0);
		return (NULL);
	}
	if (split_spaces_in_substr(meta, str))
		return (free_token_meta(meta));
	if (interpret_quotes(meta, env))
		return (free_token_meta(meta));
	if (split_operator(meta))
		return (free_token_meta(meta));
	if (interpret_env(meta, env))
		return (free_token_meta(meta));
	split_spaces(meta, env);
	modify_init_to_arg(meta);
	union_args_to_one(meta);
	delete_space_token(meta);
	syntax_error(meta);
	//todo: EMPTY 토큰 처리 및 릭 잡기 및 에러 끝내기 그리고 시그널 처리
	return (meta);
}
