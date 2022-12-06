/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:11:20 by hkong             #+#    #+#             */
/*   Updated: 2022/12/06 17:41:27 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_MAX
# define PATH_MAX	1024
#endif

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
int				is_white_space(char c);
void			set_start_end(size_t *start, size_t *end, \
							size_t start_num, size_t end_num);
#endif