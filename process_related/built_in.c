#include "../minishell.h"

/* 구현해야 하는 쉘 빌트인 함수들을 열거형을 이용해 나열했습니다 */
enum	built_in_code
{
	echo = 1,
	cd,
	pwd,
	export,
	unset,
	env,
	exit
};

/*	빌트인 echo 함수입니다. -n 옵션을 지원합니다.
	original : echo [-n] [string ...] */
int	ft_echo(char *buf, int n_option)
{
	int		write_ret;
	char	*printing_buf;

	if (n_option)
		printing_buf = ft_strjoin(buf, "");
	else
		printing_buf = ft_strjoin(buf, "\n");
	if (!printing_buf)
		return (1);
	write_ret = write(1, printing_buf, ft_strlen(printing_buf));
	free(printing_buf);
	if (write_ret == -1)
		return (1);
	else
		return (0);
}

/* 들어온 커맨드가 빌트인 함수를 호출하는 지 판단하는 함수입니다. */
int	is_built_in(char *com)
{
	if (!ft_strncmp(com, "echo", 4))
		return (echo);
	else if (!ft_strncmp(com, "cd", 2))
		return (cd);
	else if (!ft_strncmp(com, "pwd", 3))
		return (pwd);
	else if (!ft_strncmp(com, "export", 6))
		return (export);
	else if (!ft_strncmp(com, "unset", 5))
		return (unset);
	else if (!ft_strncmp(com, "env", 3))
		return (env);
	else if (!ft_strncmp(com, "exit", 4))
		return (exit);
	else
		return (0);
}

/*	빌트인 함수 실행을 준비하는 함수입니다. */
int	exec_built_in(int built_in_code)
{
	int	ret;
	if (built_in_code == echo)
		g_exit_status = ft_echo(buf, n_option);
	else if (built_in_code == cd)
	else if (built_in_code == pwd)
	else if (built_in_code == export)
	else if (built_in_code == unset)
	else if (built_in_code == env)
	else if (built_in_code == exit)
}
