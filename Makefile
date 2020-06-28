# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnails <cnails@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/17 17:12:53 by wkraig            #+#    #+#              #
#    Updated: 2020/06/28 21:58:32 by cnails           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wkraig.filler

SRCS := main.c
SRCS +=	init.c
# SRCS +=	src/get_data.c
# SRCS +=	src/check_pos.c

FLAGS = -Wall -Werror -Wextra -I./includes

OBJ = $(SRCS:.c=.o)

all: $(NAME)

newline:
		@echo "\033[38;5;166m\033[0m\n"

$(NAME): $(OBJ)
	@make -C libft
	@gcc -o $(NAME) $(FLAGS) $(OBJ) libft/libft.a
	@echo "Filler done"

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
