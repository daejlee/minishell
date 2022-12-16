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
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
CC = cc
OBJ = ./libft/ft_atoi.o ./libft/ft_bzero.o ./libft/ft_calloc.o ./libft/ft_isalnum.o ./libft/ft_isalpha.o ./libft/ft_isascii.o ./libft/ft_isdigit.o ./libft/ft_isprint.o ./libft/ft_itoa.o ./libft/ft_memchr.o ./libft/ft_memcmp.o ./libft/ft_memcpy.o ./libft/ft_memmove.o ./libft/ft_memset.o ./libft/ft_putchar_fd.o ./libft/ft_putendl_fd.o ./libft/ft_putnbr_fd.o ./libft/ft_putstr_fd.o ./libft/ft_split.o ./libft/ft_strchr.o ./libft/ft_strdup.o ./libft/ft_striteri.o ./libft/ft_strjoin.o ./libft/ft_strlcat.o ./libft/ft_strlcpy.o ./libft/ft_strlen.o ./libft/ft_strmapi.o ./libft/ft_strncmp.o ./libft/ft_strnstr.o ./libft/ft_strrchr.o ./libft/ft_strtrim.o ./libft/ft_substr.o ./libft/ft_tolower.o ./libft/ft_toupper.o ./libft/ft_lstadd_back.o ./libft/ft_lstadd_front.o ./libft/ft_lstclear.o  ./libft/ft_lstdelone.o ./libft/ft_lstiter.o ./libft/ft_lstlast.o ./libft/ft_lstmap.o ./libft/ft_lstnew.o ./libft/ft_lstsize.o
FT_PRINTF_OBJ = ./ft_printf/ft_printf.o ./ft_printf/ft_write_c.o ./ft_printf/ft_write_d.o ./ft_printf/ft_write_i.o ./ft_printf/ft_write_p.o ./ft_printf/ft_write_per.o ./ft_printf/ft_write_s.o ./ft_printf/ft_write_u.o ./ft_printf/ft_write_lowerx.o ./ft_printf/ft_write_upperx.o ./ft_printf/check_flag.o ./ft_printf/check_precision.o ./ft_printf/check_specifier.o ./ft_printf/check_width.o ./ft_printf/process_raw_str.o ./ft_printf/collect_format.o ./ft_printf/print_res_str.o ./ft_printf/num_no_padding.o ./ft_printf/num_padding_flag.o ./ft_printf/num_padding_noflag.o ./ft_printf/ptr_null.o ./ft_printf/str_or_char_flag.o ./ft_printf/str_or_char_noflag.o ./ft_printf/str_or_char_null.o
GNL_OBJ = ./gnl/get_next_line.o ./gnl/get_next_line_utils.o

all : $(NAME)

$(NAME) :
	make -C libft/ all
	make -C ft_printf/ all
	make -C gnl/ all
	ar rcs $(NAME) $(OBJ) $(FT_PRINTF_OBJ) $(GNL_OBJ)

clean :
	make -C libft/ clean
	make -C ft_printf/ clean
	make -C gnl/ clean

fclean :
	make -C libft/ fclean
	make -C ft_printf/ clean
	make -C gnl/ clean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all
