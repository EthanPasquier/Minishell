# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 09:17:42 by jalevesq          #+#    #+#              #
#    Updated: 2023/04/01 11:36:36 by jalevesq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC_DIR		= srcs/

EXEC = 	child_process executor redir_back redir_front child_pipe utils_exec utils_redir child_error

MAIN = Minishell

PARSING = Parser Split_input syntax

TOOLS = utils signal error init

SRC = $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  	$(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  	$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  	$(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \

OBJ_DIR = objs/
OBJ		= $(addprefix $(OBJ_DIR), $(subst srcs/,,$(SRC:.c=.o)))

INCLUDE		= include/

LIBFT		= libft/libft.a

LIBRLINE = readline-8.2
LIBRD	=	include/readline/libreadline.a include/readline/libhistory.a

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror -g

LIBS	= $(LIBFT) -lcurses $(LIBRD)

.PHONY: all clean fclean re cleanlib

$(OBJ_DIR)%.o:	srcs/%.c
		mkdir -p $(dir $@)
		-$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

all:	$(NAME)

$(NAME): $(LIBFT) $(LIBRD) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(LIBFT):
		make -C libft/

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

clean:
		rm -f $(OBJ) $(LIBFT)
		make -C libft/ clean
		rm -rf $(OBJ_DIR)

fclean:		clean
		rm -f $(NAME) $(NAME_BONUS)

re:		fclean all

cleanlib:	
	cd include/ && rm -rf readline