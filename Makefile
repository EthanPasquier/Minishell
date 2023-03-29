NAME	= minishell

SRC_DIR		= srcs/

EXEC = 	child_process executor child_great child_pipe utils_exec

MAIN = Minishell

PARSING = Parser Split_input

TOOLS = Utils Signal Error1 Init

SRC = $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  	$(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  	$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  	$(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \

OBJ		= $(SRC:.c=.o)

INCLUDE		= include/

LIBFT		= libft/libft.a

LIBRLINE = readline-8.2
LIBRD	=	include/readline/libreadline.a include/readline/libhistory.a

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror -g

LIBS	= $(LIBFT) -lcurses $(LIBRD)


.PHONY: all clean fclean re cleanlib

%.o:		%.c
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

fclean:		clean
		rm -f $(NAME) $(NAME_BONUS)

re:		fclean all

cleanlib:	
	cd include/ && rm -rf readline