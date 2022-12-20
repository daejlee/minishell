#include "../minishell.h"
#include "process.h"

//	ARG	I_R	ARG		P	ARG		ARG		O_R	ARG
//	cat	<	infile	|	grep	"now"	>	outfile
int	get_pcs(t_token_meta *meta, t_env *env, char **envp)
{
	t_pcs	p;
	t_token	*now;

	init_p(&p);
	p.envp = envp;
	now = get_i_redir_location(meta); //재지향 토큰 순서는 2번째가 아닐 수 있다.
	if (now->type == I_REDIR)
		p.infile_fd = open(now->next->str, O_RDONLY);
	else if (now->type == I_HRDOC)
		here_doc_seg(&p, meta);
	if (p.infile_fd == -1)
		perror("pipex error");
	now = get_o_redir_location(meta);
	if (now->type == O_APPND)
		p.outfile_fd = open(now->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (now->type == O_REDIR)
		p.outfile_fd = open(now->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (p.outfile_fd == -1)
		return (err_terminate(&p));
	p.pfd = p.pfd_arr[0];
	p.next_pfd = p.pfd_arr[1];
	return (exec_fork(&p, meta, env));
}
