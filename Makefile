# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 14:13:00 by vkuikka           #+#    #+#              #
#    Updated: 2022/02/16 01:49:42 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = main.c ls_dir.c ls_dir_utils.c print.c print_2.c names.c print_permissions.c sort_alpha.c sort_time.c sort_utils.c print_unfound.c print_unfound_newline.c
FILES = $(addprefix src/, $(SRC))
LIB = libft/libft.a
HEADERS = -I libft/includes/
FLAGS = -Wall -Wextra -Werror

$(NAME):
	@make -C libft
	gcc -o $(NAME) $(FLAGS) $(FILES) $(LIB) $(HEADERS)

clean:
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

re: fclean
	make
