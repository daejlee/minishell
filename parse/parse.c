/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:22:23 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 13:32:49 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//todo: 릭 잡기, 일관된 에러 처리 확인, 시그널 처리
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

	meta = init_token_meta();
	if (!meta)
	{
		print_error(MALLOC_FAIL, 0);
		return (NULL);
	}
	if (split_spaces_in_substr(meta, str))
	{
		free(str);
		return (free_token_meta(meta));
	}
	free(str);
	if (interpret_quotes(meta, env) || split_operator(meta) \
		|| interpret_env(meta, env) || split_spaces(meta) \
		|| modify_init_to_arg(meta) || union_args_to_one(meta) \
		|| delete_space_token(meta) || syntax_error(meta) \
		|| modify_arg_to_limiter(meta) || delete_empty_token(meta))
		return (free_token_meta(meta));
	if (!meta->size)
		return (free_token_meta(meta));
	return (meta);
}
