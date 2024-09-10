CC = cc
FLAGS = -Wall -g -Werror -Wextra
NAME = pipex
SRC = pipex.c pipex_utils.c free_exec.c ../builtins/builtins.c ../builtins/pwd.c ../builtins/echo.c ../builtins/cd.c ../builtins/env.c ../builtins/exit.c ../builtins/unset.c ../builtins/export.c ../builtins/export_utils.c test.c
INCLUDES = ./includes/
LIBFT = ../libft/libft.a
OBJ = $(SRC:.c=.o)

all : $(LIBFT) $(NAME)

%.o : %.c
	$(CC) -c $< -o $@ -I $(INCLUDES)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

prog : all
	@./pipex

ll : all
	@clear
	@./pipex

vv : all
	@clear
	@valgrind --trace-children=yes --leak-check=full ./pipex

$(LIBFT) :
	@make -C ../libft

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	@make fclean -C ../libft

re : fclean all

.PHONY: all clean fclean re
