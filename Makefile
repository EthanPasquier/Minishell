# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 09:17:42 by jalevesq          #+#    #+#              #
#    Updated: 2023/04/27 09:45:21 by jalevesq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC_DIR		= srcs/

BUILT = pwd env exit echo unset cd export builtins_set built_utils_1 built_utils_2 built_utils_3

EXEC = 	child_process executor redirections child_pipe exec_utils \
	child_error heredoc heredoc_utils exec_utils2

MAIN = Minishell

PARSING = Parser Split_input syntax syntax_error syntax_utils echo parser_utils \
	redifine split_parsing node parser_utils_v2 quote quote_utils

TOOLS = utils signal error init

SRC = $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
		$(addsuffix .c, $(addprefix srcs/built/, $(BUILT))) \
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
CFLAGS		= -Wall -Wextra -Werror

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
	cd include/ && rm -rf readline

fclean:		clean
	rm -f $(NAME) $(NAME_BONUS)

re:		fclean all
