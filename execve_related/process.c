#include "minishell.h"
#include "process.h"

int	get_pcs(t_token_meta *meta, t_env *env, char **envp)
{
	t_pcs	p;
	t_token	*now;

	init_p(&p);
	p.envp = envp;
	if (here_doc(meta, &p))
		return (1);
	terminal_set_echo();
	input_redir(meta, &p);
	output_redir(meta, &p);
	return (exec_fork(&p, meta, env));
}
