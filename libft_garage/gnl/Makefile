# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 13:56:42 by daejlee           #+#    #+#              #
#    Updated: 2022/04/29 16:01:25 by daejlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
FLAGS = -Wall -Wextra -Werror
CC = cc
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

all : $(OBJ)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean :
	rm -f $(OBJ)

re :
	$(MAKE) fclean
	$(MAKE) all
