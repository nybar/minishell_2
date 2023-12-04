# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbach <bbach@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/02 22:43:36 by bbach             #+#    #+#              #
#    Updated: 2023/12/03 13:50:01 by bbach            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	handle_quotes.c \
  	parsing.c \
	parsing_utils.c \
	init.c \
	get_any_env.c \
	execution.c 

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
