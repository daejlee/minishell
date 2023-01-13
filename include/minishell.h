/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:11:20 by hkong             #+#    #+#             */
/*   Updated: 2023/01/13 18:18:04 by daejlee          ###   ########.fr       */
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

# ifndef EMPTY_BUFFER
#  define EMPTY_BUFFER "empty_buffer"
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
	int		prev_outfile_fd;
	int		outfile_fd;
	int		infile_fd;
	int		**pfd_arr;
	char	**com;
	char	**envp;
	int		stdinout_storage[2];
	int		pcs_cnt;
	int		hdb_idx;
	int		empty_buf_flag;
	int		bad_redir_flag;
	int		single_built_in_flag;
	pid_t	*pids;
}	t_pcs;

int					g_exit_status;

#endif
