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
SRC = ft_printf.c ft_write_c.c ft_write_d.c ft_write_i.c ft_write_p.c ft_write_per.c ft_write_s.c ft_write_u.c ft_write_lowerx.c ft_write_upperx.c check_flag.c check_precision.c check_specifier.c check_width.c process_raw_str.c collect_format.c print_res_str.c num_no_padding.c num_padding_flag.c num_padding_noflag.c ptr_null.c str_or_char_flag.c str_or_char_noflag.c str_or_char_null.c
OBJ = $(SRC:.c=.o)

all : $(OBJ)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean :
	rm -f $(OBJ)

re :
	$(MAKE) clean
	$(MAKE) all
