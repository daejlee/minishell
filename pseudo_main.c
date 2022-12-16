#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* 시작 전 각종 초기화가 이뤄지는 부분 */
int	intialize(t_env **env, char **envp)
{
	int		i;
	char	**temp;
	t_env	*now;

	*env = NULL;
	temp = ft_split(envp[0], '=');
	now = init_env(temp[0], temp[1]);
	push_env(env, &now);
	i = 1;
	while (envp[i])
	{
		//free_double_arr(temp);
		temp = ft_split(envp[i], '=');
		now = init_env(temp[0], temp[1]);
		push_env(env, &now);
		i++;
	}
	//free_double_arr(temp);
	return (0);
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

	intialize(&env, envp);
	meta = init_token_meta();
	push_token(meta, init_token("ls", ARG));
	push_token(meta, init_token("|", PIPE));
	push_token(meta, init_token("grep a", ARG));
	while (1)
	{
		buf = readline("minishell 0.0.2$ ");
		//todo: buf null일 때 예외처리
		meta = parse(env, buf);
		if (get_pcs(meta, env, envp))
			return (g_exit_status);
	}
	return (0);
}
