#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* 종료 상태를 일단 전역 변수로 선언해놓았음 */
int	g_exit_status;

/* 시작 전 각종 초기화가 이뤄지는 부분 */
int	intialize(t_env *env, char **envp)
{
	int		i;
	char	**temp;
	t_env	*now;

	temp = ft_split(envp[0], '=');
	env = init_env(temp[1], temp[2]);
	now = env;
	i = 1;
	while (envp[i])
	{
		free_double_arr(temp);
		temp = ft_split(envp[i], '=');

	}
}

/* 실행부 */
int get_process();

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

	intialize(env, envp);
	while (1)
	{
		buf = readline("minishell 0.0.1$ ");
		meta = parse(buf);
		if (get_process(meta))
			return (g_exit_status);
	}
	return (0);
}
