#include "minishell.h"
#include "process.h"
#include "parse.h"

/* 시작 전 각종 초기화가 이뤄지는 부분 */
int	set_env(t_env **env, char **envp)
{
	int		i;
	char	**temp;
	t_env	*now;

	*env = NULL;
	i = 0;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (!temp)
			return (print_error(MALLOC_FAIL, 0));
		if (push_env(env, init_env(temp[0], temp[1])))
			return (print_error(MALLOC_FAIL, 0));
		free(temp);
		i++;
	}
	return (0);
}

int	terminal_init(void)
{
	struct termios	new_terminal;

	tcgetattr(0, &new_terminal);
	new_terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_terminal);
	signal(SIGINT, signal_process);
	signal(SIGQUIT, SIG_IGN);
}

/*
ex) minishell $ cat temp.txt | grep 'a'
scanner -> /cat/ /temp.txt/ /|/ /grep/ /'a'/로 분리 후 링크드 리스트로 저장
parser -> 링크드 리스트를 순회하며 이진 트리 구성 -> 하지만 멘데토리 한정에서는 링크드 리스트로 구현하는 것이 나을 수 있다.
*/

int	main(int argc, char **argv, char **envp)
{
	char			*buf;
	t_token_meta	*meta;
	t_env			*env;
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal_init();
	set_env(&env, envp);
	meta = NULL;
	while (1)
	{
		buf = readline("minishell 0.1.3$ ");
		if (buf)
		{
			if (ft_strlen(buf))
				add_history(buf);
			meta = parse(env, buf);
			if (!meta)
				continue ;
			// t_token *node;
			// node = meta->head;
			// for (int i = 0; i < meta->size; i++)
			// {
			// 	printf("%s|%s|%d\n", node->str, node->origin_str, node->type);
			// 	node = node->next;
			// }
			g_exit_status = get_pcs(meta, env, envp);
			free_token_meta(meta);
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
	tcsetattr(0, TCSANOW, &terminal);
	return (0);
}
