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

typedef struct	s_token
{
	char							*str;
	enum e_token_type	type;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct	s_token_meta
{
	size_t	size;
	t_token	*head;
}	t_token_meta;

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

#endif