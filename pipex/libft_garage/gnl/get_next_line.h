/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:04:40 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/28 15:04:42 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

typedef struct g_list
{
	char			*str;
	int				fd;
	struct g_list	*next;
	int				fst_call;
	char			*last_ret;
	int				eof_flag;
}	t_list;

t_list			*g_lstnew(int fd);
void			*g_lstdel(t_list **targ_adr, char *buf, t_list **head_adr);
unsigned int	g_strlcpy(char *dst, const char *src, unsigned int size);
unsigned int	g_strlen(const char *s);
char			*concat_buf(char *str, char *buf, int r_flag);
char			*get_next_line(int fd);

#endif
