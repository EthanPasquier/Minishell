SRC_DIR		= srcs/

_SRC		= 01-Minishell.c \
	02-Parser.c \
	03-Executor.c \
	11-Utils.c \
	12-end.c \
	13-init.c \

SRC_M		= $(addprefix $(SRC_DIR), $(_SRC))

OBJ_M		= $(SRC_M:.c=.o)

INCL		= include/

LIBFT		= libft/libft.a

LIBRD_DIR		=	$(INCL)/readline
LIBRD_FILES		=	libreadline.a libhistory.a
LIBRD_MAKEFILE		=	$(LIBRD_DIR)/Makefile
LIBRD			=	$(addprefix $(LIBRD_DIR)/, $(LIBRD_FILES))

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

LIBS	= $(LIBFT) -lcurses $(LIBRD)

NAME	= minishell

%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@


$(NAME):	$(LIBFT) $(LIBRD_MAKEFILE) $(LIBRD) $(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M) $(LIBS)

$(LIBRD): 	$(LIBRD_MAKEFILE)
		@$(MAKE) -s -C $(LIBRD_DIR)

$(LIBRD_MAKEFILE):
		@cd $(LIBRD_DIR) && ./configure --silent
$(LIBFT):
		make -C libft/

all:	$(NAME) $(NAME_BONUS) 

clean:
		rm -f $(OBJ_M) $(OBJ_B) $(LIBFT)
		make -C libft/ clean
#		@$(MAKE) -s clean -C $(LIBRD_DIR)

fclean:		clean
		rm -f $(NAME) $(NAME_BONUS)

re:		fclean all