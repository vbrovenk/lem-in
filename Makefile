# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/05 13:37:30 by vbrovenk          #+#    #+#              #
#    Updated: 2018/08/05 13:37:34 by vbrovenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
INCLUDE = lemin.h
LIBFT_INC = ./libft/includes/
LIBFT = libft/libft.a
SRC =	main.c\
		queue.c\
		move_ants.c\
		matrix.c\
		get_shortest_paths.c\
		find_path.c\
		useful_func.c\
		error.c\
		check_funcs.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

OFF=\033[0m
RED=\033[31m
REDBOLD=\033[1;31m
GREEN=\033[32m
GREENBOLD=\033[1;32m
YELLOW=\033[33m
YELLOWBOLD=\033[1;33m
PURPLE=\033[35m
PURPLEBOLD=\033[1;35m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(PURPLEBOLD)lem-in is ready"

%.o: %.c $(INCLUDE)
	@gcc $(CFLAGS) -c $< -o $@ -I $(LIBFT_INC)

clean:
	@make clean -C libft/
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME)

re: fclean all
