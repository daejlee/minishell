# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 20:51:25 by daejlee           #+#    #+#              #
#    Updated: 2022/12/16 16:55:23 by hkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = #-Wall -Wextra -Werror
LDLN_FLAG = -lreadline -L/usr/lib/x86_64-linux-gnu -I/usr/include #-L/usr/local/Cellar/readline/8.2.1/lib -I/usr/local/Cellar/readline/8.2.1/include
CC = cc

SRCS = pseudo_main.c token_list.c string_utils.c env_list.c

PARSE_DIR = parse/
SRCS_PARSE = parse.c interpret_env.c interpret_quotes.c

BUILT_IN_DIR = built_in_related/
SRCS_BUILT_IN = ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c built_in.c

EXECVE_DIR = execve_related/
SRCS_EXECVE = process.c process_exec.c process_fd_utils.c process_utils_1.c process_utils_2.c

OBJ_FILES = $(SRCS:%.c=%.o) $(SRCS_BUILT_IN:%.c=$(BUILT_IN_DIR)%.o) $(SRCS_PARSE:%.c=$(PARSE_DIR)%.o)

TEST_SRCS = $(SRCS:%.c=%.c) $(SRCS_BUILT_IN:%.c=$(BUILT_IN_DIR)%.c) $(SRCS_PARSE:%.c=$(PARSE_DIR)%.c) $(SRCS_EXECVE:%.c=$(EXECVE_DIR)%.c)

LIBFT = ./libft_garage/libft.a
LIBFT_DIR = ./libft_garage

all : $(NAME)

$(NAME) : $(OBJ_FILES) $(LIBFT)
	cc -o $(NAME) -g $(TEST_SRCS) ./libft_garage/libft/*.c ./libft_garage/ft_printf/*.c ./libft_garage/gnl/*.c $(LDLN_FLAG)
#	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -lft -L$(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	cd $(LIBFT_DIR); $(MAKE)

clean :
	make -C libft_garage/ clean
	rm -f $(OBJ_FILES) $(BONUS_OBJ)

fclean :
	make -C libft_garage/ fclean
	rm -f $(OBJ_FILES) $(BONUS_OBJ) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all
