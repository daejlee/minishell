/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:11:20 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 01:05:49 by daejlee          ###   ########.fr       */
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
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"

# ifndef PATH_MAX
#  define PATH_MAX	1024
# endif

enum	e_token_type {
	INIT = 1,
	ARG,
	PIPE,
	I_REDIR,
	O_REDIR,
	I_HRDOC,
	LIMITER,
	O_APPND,
	BLANK,
	EMPTY
};

enum	e_built_in_code
{
	B_ECHO = 1,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
};

enum	e_error_code
{
	MALLOC_FAIL,
	SYNTAX_ERROR,
	AMBIGUOUS_REDIR,
	UNEXPECTED
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

typedef struct s_ft_cd
{
	char	*env_home;
	char	*env_cdpath;
	char	*env_pwd;
	t_env	*node;
}	t_ft_cd;

typedef struct s_ft_export
{
	t_env			*head;
	t_env			*temp;
	t_env			**arr;
	int				size;
	int				i;
	int				k;
	unsigned int	len;
}	t_ft_export;

typedef struct s_hrdc_seg
{
	char	*limiter;
	int		here_doc_fd;
	char	*ret;
	int		fst_flag;
	char	*temp;
	char	*buf;
}	t_hrdc_seg;

enum	e_redir_flag
{
	I_ONLY,
	O_ONLY,
	I_O_BOTH,
	NONE
};

typedef struct s_pcs
{
	char	**here_doc_buffers;
	int		outfile_fd;
	int		infile_fd;
	int		**pfd_arr;
	char	**com;
	char	**envp;
	int		stdinout_storage[2];
	pid_t	*pids;
}	t_pcs;

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
 * utils/signal.c
 */

void				sig_excute_process(int sig);
void				sig_heredoc_process(int sig);
void				sig_main_process(int sig);

void				signal_default(void);
void				signal_execute(void);
void				signal_ignore(void);
void				signal_heredoc(void);

/**
 * utils/terminal.c
 */

void				terminal_unset_echo(void);
void				terminal_set_echo(void);

/**
 * utils/error.c
 */

int					print_error(enum e_error_code error_code, char *str);
int					quote_syntax_error(char *str, size_t end);
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

/**
 * built_in_related
 */

int					is_built_in(char *com);
int					is_echo(char *buf);
int					is_pwd(char *buf);
int					is_env(char *buf);
int					is_built_in(char *com);
int					exec_built_in(char **com, t_env *env);
int					ft_cd(char *dir, t_env *env);
int					check_cdpath(char **curpath_adr, char *env_cdpath);
char				*get_env_val(char *key, t_env *env);
int					exec_ft_echo(char **com);
int					ft_echo(char **com);
int					ft_env(t_env *env);
int					ft_exit(void);
int					ft_export(char *name, t_env *env);
int					ft_pwd(void);
int					ft_unset(char *name, t_env *env);
char				*ft_strjoin_modified(char const *s1, char const *s2, char c);

#endif
