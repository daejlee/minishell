/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:11:20 by hkong             #+#    #+#             */
/*   Updated: 2022/12/08 17:38:08 by hkong            ###   ########.fr       */
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

# ifndef PATH_MAX
#  define PATH_MAX	1024
# endif

enum	e_token_type {
	WORD,
	PIPE,
	OPTION,
	I_REDIR,
	O_REDIR,
	I_HRDOC,
	O_APPND
};

/*	구현해야 하는 쉘 빌트인 함수들을 열거형을 이용해 나열했습니다	*/
enum	e_built_in_code
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

typedef struct s_token
{
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

/*
 * token_list.c
 * t_token 리스트는 queue형태로 push/pop이 진행됨
 */

t_token_meta	*init_token_meta(void);
t_token			*init_token(char *str);
int				push_token(t_token_meta *meta, t_token *node);
t_token			*pop_token(t_token_meta *meta);
t_token_meta	*free_token_meta(t_token_meta *meta);

/*
 * parse.c
 */

t_token			*lexical_analyzer(char *str);
void			set_start_end(size_t *start, size_t *end, \
							size_t start_num, size_t end_num);

/*
 * env_list.c
 * env 관련 함수 실행을 위한 utils가 있는 파일.
 */

/*
 * about env.
 * 빈 문자열이 env의 value인 것은 O, key로 두는 것은 X
 * '='을 기준으로 파싱, 여러 개라면 맨 처음에 있는 것을 기준!
 * '='이 없다면, env에 저장되지 않는다.
 */

t_env			*init_env(char *key, char *value);
int				push_env(t_env *head, t_env	*node);
int				delete_env(t_env *head, char *key);
t_env			*find_env(t_env *head, char *key);

/*
 * string_utils.c
 */

int				is_whitespace(char c);
int				is_exactly_same(char *str1, char *str2);


#endif