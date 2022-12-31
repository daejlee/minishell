/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:11:20 by hkong             #+#    #+#             */
/*   Updated: 2022/12/30 21:38:30 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "./libft_garage/libft/libft.h"
# include "./libft_garage/ft_printf/ft_printf.h"

# ifndef PATH_MAX
#  define PATH_MAX	1024
# endif

enum	e_token_type {
	INIT = 1,
	ARG, // ex) echo -n 이 있으면 [echo -n]이 통째로 ARG인 형식을 따르는 게 좋을 것 같습니다.
	PIPE,
	I_REDIR,
	O_REDIR,
	I_HRDOC,
	LIMITER, // here_doc에 필요한 리미터입니다.
	O_APPND,
	BLANK,
	EMPTY
};

/*	구현해야 하는 쉘 빌트인 함수들을 열거형을 이용해 나열했습니다	*/
enum	e_built_in_code
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum	e_error_code
{
	MALLOC_FAIL,
	SYNTAX_ERROR,
	AMBIGUOUS_REDIR,
};

typedef struct s_token
{
	char				*origin_str;
	char				*str;
	enum e_token_type	type;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_token_meta
{
	size_t	size;
	t_token	*head;
}	t_token_meta;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

/* 종료 상태를 일단 전역 변수로 선언해놓았음 */
int					g_exit_status;

/**
 * token.c
 * t_token 리스트는 queue형태로 push/pop이 진행됨
 */

t_token				*init_token(char *str, enum e_token_type type);
int					push_token(t_token_meta *meta, t_token *node);
t_token				*pop_token(t_token_meta *meta);
void				free_token(t_token *token);
int					set_token_origin(t_token *token, char *str);

/**
 * token_meta.c
 * t_token 리스트는 queue형태로 push/pop이 진행됨
 */

t_token_meta		*init_token_meta(void);
t_token_meta		*free_token_meta(t_token_meta *meta);

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
int					interpret_env_in_substr(char **str, t_env *env);
int					change_key_to_value(char **str, t_env *env, \
													size_t *start, size_t end);
int					insert_value_on_index(char **str, char *value, \
													size_t start, size_t end);
int					is_env_allowed_char(int is_first, char c);

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

void				modify_init_to_arg(t_token_meta *meta);
int					union_args_to_one(t_token_meta *meta);
int					delete_space_token(t_token_meta *meta);

/**
 * parse/syntax_error.c
 */
int					syntax_error(t_token_meta *meta);

/**
 * utils/error.c
 */

int					print_error(enum e_error_code error_code, char *str);

/**
 * env_list.c
 * env 관련 함수 실행을 위한 utils가 있는 파일.
 */

/**
 * about env.
 * 빈 문자열이 env의 value인 것은 O, key로 두는 것은 X
 * '='을 기준으로 파싱, 여러 개라면 맨 처음에 있는 것을 기준!
 * '='이 없다면, env에 저장되지 않는다.
 */

t_env				*init_env(char *key, char *value);
int					push_env(t_env **head, t_env	**node);
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

/**
 * number_utils.c
 */

void				initialize_numbers(size_t *num1, size_t *num2, \
												size_t *num3, size_t *num4);

void				set_start_end(size_t *start, size_t *end, \
										size_t start_num, size_t end_num);

/**
 * built_in_related
 */

int	is_built_in(char **com);
int	exec_built_in(char **com, t_env *env);
int	ft_cd(char *dir, t_env *env);
int	exec_ft_echo(char **com);
int	ft_echo(char *buf, int n_option);
int	ft_env(t_env *env);
int	ft_exit(void);
int	ft_export(char *name, t_env *env);
int	ft_pwd(void);
int	ft_unset(char *name, t_env *env);

int	get_pcs(t_token_meta *meta, t_env *env, char **envp);


#endif
