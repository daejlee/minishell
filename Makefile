# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkong <hkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 20:51:25 by daejlee           #+#    #+#              #
#    Updated: 2022/12/09 20:23:28 by hkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LDLN_FLAG = -lreadline -L/usr/lib/x86_64-linux-gnu -I/usr/include #-L/usr/local/Cellar/readline/8.2.1/lib -I/usr/local/Cellar/readline/8.2.1/include
CC = cc
BUILT_IN_DIR = built_in_related/
SRCS = pseudo_main.c parse.c token_list.c string_utils.c env_list.c
SRCS_BUILT_IN = built_in_related/ft_echo.c built_in_related/ft_env.c built_in_related/ft_exit.c built_in_related/ft_export.c built_in_related/ft_pwd.c built_in_related/ft_unset.c
OBJ_FILES = $(SRCS:%.c=%.o) $(SRCS_BUILT_IN:$(FILE_DIR)%.c=%.o)
LIBFT = ./libft_garage/libft.a
LIBFT_DIR = ./libft_garage

all : $(NAME)

$(NAME) : $(OBJ_FILES) $(LIBFT)
	cc -o $(NAME) -g $(SRCS) $(SRCS_BUILT_IN) ./libft_garage/libft/*.c ./libft_garage/ft_printf/*.c ./libft_garage/gnl/*.c $(LDLN_FLAG)
#	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -lft -L$(LIBFT_DIR)

$(OBJ_FILES) : $(SRCS) $(SRCS_BUILT_IN)
	$(CC) $(CFLAGS) -c $(SRCS) $(SRCS_BUILT_IN)

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
