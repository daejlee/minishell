/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:00:08 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 13:01:11 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"

/**
 * token.c
 */

t_token				*init_token(char *str, enum e_token_type type);
int					push_token(t_token_meta *meta, t_token *node);
t_token				*pop_token(t_token_meta *meta);
void				free_token(t_token *token);
int					set_token_origin(t_token *token, char *str);

/**
 * token_meta.c
 */

t_token_meta		*init_token_meta(void);
t_token_meta		*free_token_meta(t_token_meta *meta);

/**
 * signal.c
 */

void				signal_default(void);
void				signal_execute(void);
void				signal_ignore(void);
void				signal_heredoc(void);

/**
 * signal_func.c
 */

void				sig_excute_process(int sig);
void				sig_heredoc_process(int sig);
void				sig_main_process(int sig);


/**
 * terminal.c
 */

void				terminal_unset_echo(void);
void				terminal_set_echo(void);

/**
 * error.c
 */

int					print_error(enum e_error_code error_code, char *str);
int					quote_syntax_error(char *str, size_t end);

/**
 * env_list.c
 */

t_env				*init_env(char *key, char *value);
int					push_env(t_env **head, t_env *node);
int					delete_env(t_env *head, char *key);
t_env				*find_env(t_env *head, char *key);

/**
 * string_utils.c
 */

int					is_exactly_same(char *str1, char *str2);
int					ok_and_free_multiple_str(char *str1, char *str2, \
												char *str3, char *str4);
int					fail_and_free_multiple_str(char *str1, char *str2, \
												char *str3, char *str4);
int					is_env_allowed_char(int is_first, char c);
int					set_two_string(char **str1, char *new_str1, \
										char **str2, char *new_str2);

/**
 * number_utils.c
 */

void				initialize_numbers(size_t *num1, size_t *num2, \
												size_t *num3, size_t *num4);
void				set_start_end(size_t *start, size_t *end, \
										size_t start_num, size_t end_num);


#endif