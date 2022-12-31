#ifndef HERE_DOC_INPUT_BUFFER
# define HERE_DOC_INPUT_BUFFER "here_doc_input_buffer"
#endif

#ifndef PROCESS_H
# define PROCESS_H
# include <unistd.h>
# include "../minishell.h"

enum	e_redir_flag
{
	I_ONLY,
	O_ONLY,
	I_O_BOTH,
	NONE
};

typedef struct s_pcs
{
	int		here_doc_flag;
	int		outfile_fd;
	int		infile_fd;
	int		temp_infile_fd;
	int		pfd_arr[2][2];
	int		*pfd;
	int		*next_pfd;
	char	**com;
	char	**envp;
	int		stdinout_storage[2];
	pid_t	*pids;
}	t_pcs;

/**
 * process_exec.c
 */

void		exec_com(t_pcs *p, t_token *now, t_env *env);
int			here_doc_seg(t_pcs *p, t_token *now);
int			exec_fork(t_pcs *p, t_token_meta *meta, t_env *env);

/**
 * process_fd_utils.c
 */

void		swap_pfd(int **pfd1, int **pfd2);
void		prep_fds(t_pcs *p, int i, int pcs_cnt, t_token_meta *meta, int stdinout_storage[2]);
void		reset_fds(t_pcs *p, int stdin_dup, int stdout_dup);

/**
 * process_utils_1.c
 */

t_token		*get_i_redir_location(t_token_meta *meta);
t_token		*get_o_redir_location(t_token_meta *meta);
int			get_pcs_cnt(t_token_meta *meta);
int			free_arr(char **com);
char		*ft_strjoin_modified(char const *s1, char const *s2);

/**
 * process_utils_2.c
 */

int			wait_for_children(t_pcs *p, pid_t *pids, int temp);
int			err_terminate(t_pcs *p);
void		execve_failed(t_pcs *p, char *sh_func);
void		init_p(t_pcs *p);
int			check_redir(t_token_meta *meta);

#endif
