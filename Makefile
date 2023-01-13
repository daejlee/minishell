# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 20:51:25 by daejlee           #+#    #+#              #
#    Updated: 2023/01/13 15:05:16 by daejlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -f

INCLUDE = -I./include -I/Users/daejlee/.brew/opt/readline/include
LIBRARY = -lreadline -L/Users/daejlee/.brew/opt/readline/lib -lft -L$(LIBFT_DIR)

SRCS = main.c

PARSE_DIR = parse/
SRCS_PARSE = parse.c interpret_env.c interpret_quotes.c split_spaces.c split_operator.c modify_arg.c syntax_error.c union_arg.c

BUILT_IN_DIR = built_in/
SRCS_BUILT_IN = ft_echo.c ft_env.c ft_exit.c ft_export.c ft_export_utils.c ft_pwd.c ft_unset.c built_in.c ft_cd.c ft_cd_utils.c built_in_utils.c

EXECVE_DIR = execve/
SRCS_EXECVE = process.c process_hrdc.c process_hrdc_utils.c process_redir.c process_exec.c process_exec_utils_1.c process_exec_utils_2.c process_exec_utils_3.c process_fd_utils_1.c process_fd_utils_2.c process_utils_1.c process_utils_2.c process_utils_3.c

UTILS_DIR = utils/
SRCS_UTILS = env_list.c token.c token_meta.c string_utils_1.c string_utils_2.c number_utils.c error.c signal.c signal_func.c terminal.c

OBJ_FILES = $(SRCS:%.c=%.o) $(SRCS_BUILT_IN:%.c=$(BUILT_IN_DIR)%.o) $(SRCS_PARSE:%.c=$(PARSE_DIR)%.o) $(SRCS_UTILS:%.c=$(UTILS_DIR)%.o) $(SRCS_EXECVE:%.c=$(EXECVE_DIR)%.o)

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

all : $(NAME)

debug: $(NAME)

$(NAME) : $(OBJ_FILES)
	$(MAKE) all -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(LIBRARY) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_FILES)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all
