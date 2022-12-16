/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:21:19 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/22 18:21:20 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>

typedef struct s_info
{
	char			spc;
	char			*flag;
	int				width;
	int				precision;
	int				length;
	unsigned int	padding;
	char			*raw_str;
	char			*res_str;
}	t_info;

int		ft_printf(const char *str, ...);
int		collect_format(const char *str, struct s_info *p, va_list ap);
int		print_res_str(struct s_info *p);
char	*process_raw_str(struct s_info *p);
char	*check_specifier(va_list ap, const char *str);
int		check_precision(const char *str, va_list ap);
int		check_width(const char *str, va_list ap);
char	*check_flag(const char *str);
char	*ft_write_c(va_list ap);
char	*ft_write_s(va_list ap);
char	*ft_write_p(va_list ap);
char	*ft_write_d(va_list ap);
char	*ft_write_i(va_list ap);
char	*ft_write_u(va_list ap);
char	*ft_write_lowerx(va_list ap);
char	*ft_write_upperx(va_list ap);
char	*ft_write_per(va_list ap);
void	num_no_padding(struct s_info *p, int raw_strlen);
void	num_padding_flag(struct s_info *p, unsigned int padding, int slots);
void	num_padding_noflag(struct s_info *p,
			unsigned int padding, int raw_strlen);
void	ptr_null(struct s_info *p, int raw_strlen);
void	str_or_char_flag(struct s_info *p, int raw_strlen);
void	str_or_char_noflag(struct s_info *p, int raw_strlen);
void	str_or_char_null(struct s_info *p, int raw_strlen);

#endif
