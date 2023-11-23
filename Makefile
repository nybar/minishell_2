# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbach <bbach@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 11:05:57 by bbach             #+#    #+#              #
#    Updated: 2023/11/23 11:47:01 by bbach            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	valid_input.c \
	parsing.c \
	get_env.c 


OBJS = $(SRC:.c=.o)

RM = rm -f

NAME = minishell

LIB = ./includes/libft/libft/libft.a

CC = gcc 

CFLAGS = -Wall -Werror -Wextra -g

all: ${LIB} $(NAME)

${LIB} : 
	make -s -C ./includes/libft/ all

%.o: %.c
		@${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS) ${LIB}
	@${CC} ${CFLAGS} $(OBJS) -L./includes/libft -lft -lreadline -o $(NAME)
	@echo "\033[32mCompilation done !\033[0m"

clean:
		@${RM} ${OBJS}
		@make -s -C ./includes/libft/ clean
		@echo "\033[32mObjects deleted !\033[0m"

fclean: clean
		@${RM} ${NAME}
		@make -s -C ./includes/libft/ fclean

re : fclean all

.PHONY: all clean fclean re