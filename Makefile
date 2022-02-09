# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 14:13:00 by vkuikka           #+#    #+#              #
#    Updated: 2022/02/09 19:53:47 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = main.c ls_dir.c sort.c print.c names.c print_permissions.c
FILES = $(addprefix src/, $(SRC))
LIB = libftprintf/libftprintf.a
HEADERS = -I libftprintf/ -I libftprintf/libft/includes
FLAGS = -Wall -Wextra -Werror
SDL = `sdl2-config --cflags` `sdl2-config --libs`


all:
	@make -C libftprintf
	gcc -O3 -o $(NAME) $(FILES) $(LIB) $(HEADERS) $(SDL)

f:
	gcc -O3 -fsanitize=address -g -o $(NAME) $(FILES) $(LIB) $(HEADERS) $(SDL)

clean:
	@make clean -C libftprintf

fclean: clean
	rm -f $(NAME)
	@make fclean -C libftprintf

re: fclean
	make all
