# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:49:21 by jalevesq          #+#    #+#              #
#    Updated: 2023/03/28 18:04:22 by jalevesq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		= srcs/

_SRC		= Minishell.c \
	Parser.c \
	Split_input.c \
	Executor.c \
	Utils_Exec.c \
	Signal.c \
	Utils.c \
	Error1.c \
	Init.c \
	Child_Process.c

SRC_M		= $(addprefix $(SRC_DIR), $(_SRC))

OBJ_M		= $(SRC_M:.c=.o)

INCLUDE		= include/

LIBFT		= libft/libft.a

LIBRLINE = readline-8.2
LIBRD	=	include/readline/libreadline.a include/readline/libhistory.a

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror -g

LIBS	= $(LIBFT) -lcurses $(LIBRD)

NAME	= minishell

%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(LIBFT) $(LIBRD) $(OBJ_M)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M) $(LIBS)

$(LIBFT):
		make -C libft/

all:	$(NAME)
	
$(LIBRD):
	curl -O ftp://ftp.cwru.edu/pub/bash/$(LIBRLINE).tar.gz
	tar -xf $(LIBRLINE).tar.gz
	rm -rf $(LIBRLINE).tar.gz
	cd $(LIBRLINE) && bash configure && make
	cd include/ && mkdir readline
	mv ./$(LIBRLINE)/libreadline.a ./include/readline
	mv ./$(LIBRLINE)/libhistory.a ./include/readline
	mv ./$(LIBRLINE)/*.h ./include/readline
	rm -rf $(LIBRLINE)

cleanlib:	
	cd include/ && rm -rf readline
clean:
		rm -f $(OBJ_M) $(LIBFT)
		make -C libft/ clean

fclean:		clean
		rm -f $(NAME) $(NAME_BONUS)


re:		fclean all