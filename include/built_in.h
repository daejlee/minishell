/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:17:28 by hkong             #+#    #+#             */
/*   Updated: 2023/01/11 03:03:56 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "minishell.h"

/**
 * built_in/built_in_utils.c
 */

int			is_built_in(char *com);
int			is_echo(char *buf);
int			is_pwd(char *buf);
int			is_env(char *buf);

/**
 * built_in/built_in.c
 */

int			exec_built_in(char **com, t_env *env);
static int	exec_built_in_seg(int built_in_code, char **com, t_env *env, int i);

/**
 * built_in/ft_echo.c
 */

int			ft_echo(char **com);
int			get_n_option(char **com);
char		*get_echo_str(char **com, int n_option);

#endif
