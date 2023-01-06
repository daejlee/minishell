/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:01:57 by hkong             #+#    #+#             */
/*   Updated: 2023/01/06 13:24:45 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/**
 * parse/parse.c
 */

t_token_meta		*parse(t_env *env, char *str);

/**
 * parse/interpret_quotes.c
 */

int					interpret_quotes(t_token_meta *meta, t_env *env);
int					interpret_quotes_in_substr(t_token_meta *meta, \
														char *str, t_env *env);
char				*interpret_quotes_single(t_token_meta *meta, char *str, \
																size_t start);
char				*interpret_quotes_double(t_token_meta *meta, \
										t_env *env, char *str, size_t start);
size_t				quote_index(char *str);

/**
 * parse/interpret_env.c
 */

int					interpret_env(t_token_meta *meta, t_env *env);
int					check_set_env_node(t_token *node, size_t token_num);
int					interpret_env_in_substr(char **str, t_env *env);
int					change_key_to_value(char **str, t_env *env, \
													size_t *start, size_t end);
int					insert_value_on_index(char **str, char *value, \
													size_t start, size_t end);

/**
 * parse/split_spaces.c
 */

int					split_spaces(t_token_meta *meta, t_env *env);
int					split_spaces_in_substr(t_token_meta *meta, char *str);
int					skip_quotes(char *str, size_t *end);
int					has_space(char *str);
int					has_heredoc_before(t_token *token);

/**
 * parse/split_operator.c
 */

int					split_operator(t_token_meta *meta);
int					split_operator_in_substr(t_token_meta *meta, char *str);
t_token				*create_operator_token(char *str, size_t *index);
size_t				operator_index(char *str);
enum e_token_type	operator_type(char *str);

/**
 * parse/modify_arg.c
 */

int					modify_init_to_arg(t_token_meta *meta);
int					delete_space_token(t_token_meta *meta);
int					delete_empty_token(t_token_meta *meta);
int					modify_arg_to_limiter(t_token_meta *meta);

/**
 * parse/union_arg.c
 */

int					union_args_to_one(t_token_meta *meta);
t_token				*create_union_token(size_t *num, \
										t_token_meta *meta, t_token *node);

/**
 * parse/syntax_error.c
 */

int					syntax_error(t_token_meta *meta);
int					syntax_error_redir(size_t token_num, t_token *node, \
													enum e_token_type type);
int					syntax_error_pipe(t_token_meta *meta, \
											size_t token_num, t_token *node);

#endif