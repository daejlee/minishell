/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 19:54:27 by daejlee           #+#    #+#             */
/*   Updated: 2022/08/13 19:54:28 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "pipex.h"

void	swap_pfd(int **pfd1, int **pfd2)
{
	int	*temp;

	temp = *pfd1;
	*pfd1 = *pfd2;
	*pfd2 = temp;
}

static void	prep(int input_fd, int output_fd, int closing_fd, t_pcs *p)
{
	close(closing_fd);
	if (input_fd)
	{
		dup2(input_fd, 0);
		close(input_fd);
		if (p)
			p->pfd[0] = 0;
	}
	if (output_fd != 1)
	{
		dup2(output_fd, 1);
		close(output_fd);
		if (p)
			p->next_pfd[1] = 1;
	}
}

void	prep_fds(t_pcs *p, int i, int argc)
{
	if (p->here_doc_flag)
	{
		if (i == 3)
			prep(p->infile_fd, p->next_pfd[1], 0, p);
		else if (i == argc - 2)
			prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
	else
	{
		if (i == 2)
			prep(p->infile_fd, p->next_pfd[1], 0, p);
		else if (i == argc - 2)
			prep(p->pfd[0], p->outfile_fd, p->pfd[1], NULL);
		else
			prep(p->pfd[0], p->next_pfd[1], 1, p);
	}
}

char	*ft_strjoin_modified(char const *s1, char const *s2)
{
	int				i;
	unsigned int	s1_len;
	char			*res;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 2));
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '/';
	i = 0;
	while (s2[i])
	{
		res[s1_len + 1 + i] = s2[i];
		i++;
	}
	res[s1_len + 1 + i] = '\0';
	return (res);
}

char	**ft_split_awk(char *s)
{
	char	**ret;

	if (ft_strchr(s, '\''))
		ret = ft_split(s, '\'');
	else
		ret = ft_split(s, '\"');
	if (!ret)
		return (NULL);
	ret[0][3] = '\0';
	return (ret);
}
