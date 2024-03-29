/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:17:28 by hkong             #+#    #+#             */
/*   Updated: 2023/01/13 17:41:08 by hkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
# include "utils.h"

/**
 * built_in
 */

int		ft_cd(char *dir, t_env *env);
int		ft_echo(char **com);
int		ft_env(t_env *env);
int		ft_exit(char **com);
int		ft_export(char *name, t_env *env);
int		print_sorted_env(t_env *env);
int		ft_pwd(void);
int		ft_unset(char *name, t_env *env);

/**
 * built_in.c
 */

int		exec_built_in(char **com, t_env *env);

/**
 * built_in_utils.c
 */

int		is_built_in(char *com);
int		is_echo(char *buf);
int		is_pwd(char *buf);
int		is_env(char *buf);

/**
 * ft_cd_utils.c
 */

int		check_cdpath(char **curpath_adr, char *env_cdpath);
char	*get_env_val(char *key, t_env *env);

/**
 * ft_echo.c
 */

int		get_n_option(char **com);
char	*get_echo_str(char **com, int n_option);

#endif
