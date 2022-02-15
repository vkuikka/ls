# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 14:13:00 by vkuikka           #+#    #+#              #
#    Updated: 2022/02/15 20:43:27 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = main.c ls_dir.c ls_dir_utils.c print.c print_2.c names.c print_permissions.c sort_alpha.c sort_time.c sort_utils.c
FILES = $(addprefix src/, $(SRC))
LIB = libft/libft.a
HEADERS = -I libft/includes/
FLAGS = -Wall -Wextra -Werror

all:
	@make -C libft
	gcc -O3 -o $(NAME) $(FILES) $(LIB) $(HEADERS)

f:
	gcc -O3 -fsanitize=address -g -o $(NAME) $(FILES) $(LIB) $(HEADERS)

clean:
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

re: fclean
	make all
