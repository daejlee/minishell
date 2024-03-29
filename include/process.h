/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 03:04:32 by daejlee           #+#    #+#             */
/*   Updated: 2023/01/13 16:44:08 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "minishell.h"
# include "utils.h"
# include "built_in.h"

/**
 * process.c
 */

int			get_pcs(t_token_meta *meta, t_env *env, char **envp);

/**
 * process_redir.c
 */

int			input_redir(t_token_meta *meta, t_token *now, t_pcs *p, int i);
void		output_redir(t_token_meta *meta, t_token *now, t_pcs *p);

/**
 * process_here_doc_utils.c
 */

int			get_here_doc_cnt(t_token_meta *meta);
void		get_here_doc_buffers(t_token_meta *meta, t_pcs *p);
int			here_doc(t_token_meta *meta, t_pcs *p);

/**
 * process_exec.c
 */

int			here_doc_seg(t_pcs *p, t_token *now, int i);
int			exec_fork(t_pcs *p, t_token_meta *meta, t_env *env);

/**
 * process_exec_utils_1.c
 */

void		exec_com(t_pcs *p, t_env *env);
t_token		*prep_fd_n_move(t_token *now, int i, t_token_meta *meta, t_pcs *p);
int			prep_exec_loop(t_pcs *p, t_token_meta *meta);

/**
 * process_exec_utils_2.c
 */

char		**get_com(t_token *now, t_token_meta *meta);
char		**get_trimmed_com(t_token *now, t_token_meta *meta);
int			launch_com(t_pcs *p, t_env *env, int i);
int			wrap_up_pcs(t_pcs *p, t_token_meta *meta, int stdout_dup);

/**
 * process_exec_utils_3.c
 */

t_token		*prep_bad_infile(t_pcs *p, t_token *now, t_token_meta *meta,
				int *temp_flag_adr);
t_token		*fast_forward_node(t_pcs *p, t_token *now, t_token_meta *meta,
				int i);
t_token		*prep_redir_n_com(t_pcs *p, t_token_meta *meta, t_token *now,
				int i);

/**
 * process_fd_utils.c
 */

void		prep(int input_fd, int output_fd);
void		swap_pfd(int **pfd1, int **pfd2);
void		prep_fds(t_pcs *p, int i, int pcs_cnt);
void		reset_fds(t_pcs *p, int stdinout_storage[2], int pcs_cnt);

/**
 * process_utils_1.c
 */

t_token		*get_i_redir_location(t_token_meta *meta);
t_token		*get_o_redir_location(t_token_meta *meta);
int			get_pcs_cnt(t_token_meta *meta);

/**
 * process_utils_2.c
 */

int			wait_for_children(pid_t *pids, int pcs_cnt);
void		execve_failed(char *sh_func);
void		init_p(t_pcs *p);
int			check_redir(t_pcs *p);

/**
 * process_utils_3.c
 */

void		err_terminate(t_pcs *p);
int			get_pipes(t_pcs *p, int pcs_cnt);

#endif
