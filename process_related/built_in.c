#include "../minishell.h"

/*	구현해야 하는 쉘 빌트인 함수들을 열거형을 이용해 나열했습니다	*/
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
	original : echo [-n] [string ...]	*/
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

/*	빌트인 cd 함수입니다. 상대 경로 혹은 절대 경로만을 사용합니다.
	original : cd [-L|-P] [directory]	*/
int	ft_cd(char *dir)
{
	char	*curpath;

	if (!dir && ($HOME is empty || undefined))	//1st
		return (0);
	else if (!dir)	//2nd
		dir = $HOME;
	if (dir[0] == '/')	//3rd
	{
		curpath = dir;
		GOTO 7th;
	}
	else if (!ft_strncmp(dir, "..", 2) || dir[0] == '.')	//4th
		GOTO 6th;
	if (!get_cdpath())	// 5th
		GOTO 7th;
	else	//6th
		curpath = dir;
	if (curpath[0] != '/')	//7th
	{
		if (PWD dont end with '/')
			PWD = ft_strjoin(PWD, '/');
		curpath = ft_strjoin(PWD, curpath);
	}
	get_canonical_curpath();	//8th
	trim_curpath();	//9th
	return (chdir(curpath));	//10th
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
