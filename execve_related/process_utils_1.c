#include "minishell.h"
#include "process.h"

t_token	*get_i_redir_location(t_token_meta *meta)
{
	t_token	*now;

	now = meta->head;
	if (now->type == I_REDIR || now->type == I_HRDOC)
		return (now);
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == I_REDIR || now->type == I_HRDOC)
			return (now);
		now = now->next;
	}
	return (now);
}

t_token	*get_o_redir_location(t_token_meta *meta)
{
	t_token	*now;

	now = meta->head;
	if (now->type == O_REDIR || now->type == O_APPND)
		return (now);
	now = now->next;
	while (now != meta->head)
	{
		if (now->type == O_REDIR || now->type == O_APPND)
			return (now);
		now = now->next;
	}
	return (now);
}

int	get_pcs_cnt(t_token_meta *meta)
{
	int		ret;
	t_token	*now;

	ret = 0;
	now = meta->head;
	if (now->type == ARG)
	{
		ret++;
		now = now->next;
		while (now->type != PIPE || now != meta->head)
		{
			if (now->type == PIPE)
				break ;
			while (now->type >= I_REDIR && now->type <= O_APPND)
				now = now->next->next;
			while (now->type == ARG && now != meta->head)
				now = now->next;
		}
	}
	else
		now = now->next;
	while (now != meta->head)
	{
		if (now->type == ARG)
		{
			ret++;
			now = now->next;
			while (now->type != PIPE || now != meta->head)
			{
				if (now->type == PIPE)
					break ;
				while (now->type >= I_REDIR && now->type <= O_APPND)
					now = now->next->next;
				while (now->type == ARG && now != meta->head)
					now = now->next;
			}
		}
		else
			now = now->next;
	}
	return (ret);
}

int	free_arr(char **com)
{
	unsigned int	i;

	i = 0;
	while (com[i])
		free(com[i++]);
	free(com);
	return (0);
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
