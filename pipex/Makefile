# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 20:51:25 by daejlee           #+#    #+#              #
#    Updated: 2022/08/30 16:12:58 by daejlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -Wall -Wextra -Werror
CC = cc
SRC = pipex_utils_1.c pipex_utils_2.c pipex_exec.c pipex_hd.c pipex.c
OBJ = $(SRC:.c=.o)
BONUS_SRC = pipex_utils_1_bonus.c pipex_utils_2_bonus.c pipex_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)
LIBFT = ./libft_garage/libft.a
LIBFT_DIR = ./libft_garage

ifdef WITH_BONUS
	OBJ_FILES = $(BONUS_OBJ)
	SRC_FILES = $(BONUS_SRC)
else
	OBJ_FILES = $(OBJ)
	SRC_FILES = $(SRC)
endif

all : $(NAME)

$(NAME) : $(OBJ_FILES) $(LIBFT)
	cc -o pipex -g *.c ./libft_garage/libft/*.c ./libft_garage/ft_printf/*.c ./libft_garage/gnl/*.c
#	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -lft -L$(LIBFT_DIR)

$(OBJ_FILES) : $(SRC_FILES)
	$(CC) $(CFLAGS) -c $(SRC_FILES)

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

bonus : $(NAME) $(BONUS_SRC)
	make WITH_BONUS=1 $(NAME)
