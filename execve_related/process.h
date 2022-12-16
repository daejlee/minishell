#ifndef HERE_DOC_INPUT_BUFFER
# define HERE_DOC_INPUT_BUFFER "here_doc_input_buffer"
#endif

#ifndef PROCESS_H
# define PROCESS_H
# include <unistd.h>

typedef struct s_pcs
{
	int		here_doc_flag;
	int		outfile_fd;
	int		infile_fd;
	int		pfd_arr[2][2];
	int		*pfd;
	int		*next_pfd;
	char	**com;
	char	**envp;
	pid_t	*pids;
}	t_pcs;

void		swap_pfd(int **pfd1, int **pfd2);
int			check_com_for_quote(char *com);
void		prep_fds(t_pcs *p, int i, int argc);
void		execve_failed(t_pcs *p, char *sh_func);
void		init_p(t_pcs *p);
int			free_arr(char **com);
int			err_terminate(t_pcs *p);
char		*ft_strjoin_modified(char const *s1, char const *s2);
char		**ft_split_awk(char *s);
int			wait_for_children(t_pcs *p, pid_t *pids, int temp);
void		exec_com(t_pcs *p, t_token *now, int i, t_env *env);
int			here_doc(t_pcs *p, int argc, char *argv[]);
void		exec_sh(t_pcs *p, char *argv[], int i);

#endif
