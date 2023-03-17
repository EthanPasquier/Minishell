# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 09:31:15 by jalevesq          #+#    #+#              #
#    Updated: 2023/03/17 11:48:08 by jalevesq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

INC_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = 01-Minishell.c \
	02-Lexer.c \
	03-Parser.c \
	11-Utils.c \
	12-End.c \
	13-Init.c \
	# 04-Executor.c \

OBJS = $(addprefix ${OBJS_DIR}/, ${SRCS:%.c=%.o})

LIBFT_PATH = libft
LIBFT_LIB = ${LIBFT_PATH}/libft.a
LIBFT_INC = ${LIBFT_PATH}/libft.h

LIBRD_DIR		=	include/librd
LIBRD_FILES		=	libreadline.a libhistory.a
LIBRD_MAKEFILE		=	$(LIBRD_DIR)/Makefile
LIBRD			=	$(addprefix $(LIBRD_DIR)/, $(LIBRD_FILES))

LIBS	= $(LIBFT_LIB) $(LIBRD)

GREEN	= \033[32;1m
CYAN	= \033[36;1m
RED		= \033[0;31m
BOLD	= \033[1m
RESET	= \033[0m
MAGENTA	=\033[0;95m

all: ${LIBS} ${NAME}

$(LIBRD): 	$(LIBRD_MAKEFILE)
		@$(MAKE) -s -C $(LIBRD_DIR)
	
$(LIBRD_MAKEFILE):
		@cd $(LIBRD_DIR) && ./configure --silent

${LIBFT_LIB}:
	@make -C ${LIBFT_PATH}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D}
	@${CC} ${CFLAGS} -I ${INC_DIR} -I ${LIBFT_INC} -c $< -o $@
	@echo "$(GREEN)Compiling: $<$(RESET)$(MAGENTA)              [OK]$(RESET)"

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -lreadline ${LIBFT_LIB} -o ${NAME}
	@echo "$(GREEN)Compilation terminé avec succès !"

clean:
	@make clean -C ${LIBFT_PATH}
	@${RM} ${OBJS_DIR}
	@echo "$(RED)$(BOLD)Nettoyage effectué avec succès !"

fclean:	clean
	@make fclean -C ${LIBFT_PATH}
	@${RM} ${NAME}

re: fclean all
	@echo "$(CYAN)Recompilation Terminé !"

.PHONY: all clean fclean re