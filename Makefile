NAME = minishell

SRCS = main.c

EXEC_DIR = execution
EXEC_FILES = pipex.c pipex_utils.c free_exec.c
EXEC_SRCS = $(addprefix $(EXEC_DIR)/,$(EXEC_FILES))

BUILT_DIR = builtins
BUILT_FILES = builtins.c pwd.c echo.c cd.c env.c exit.c unset.c export.c export_utils.c
BUILT_SRCS = $(addprefix $(BUILT_DIR)/,$(BUILT_FILES))

PARS_DIR = parsing
PARS_FILES = tokenize.c input.c input_utils.c command.c prompt.c environment.c syntax.c metachars.c
PARS_SRCS = $(addprefix $(PARS_DIR)/,$(PARS_FILES))

STRUCT_DIR = structs
STRUCT_FILES =  data.c entry.c token.c cmd.c arg.c parse.c
STRUCT_SRCS = $(addprefix $(STRUCT_DIR)/,$(STRUCT_FILES))

UTIL_DIR = utils
UTIL_FILES =  memory.c strjoin_free.c error.c
UTIL_SRCS = $(addprefix $(UTIL_DIR)/,$(UTIL_FILES))

OBJS = $(SRCS:.c=.o) $(EXEC_SRCS:.c=.o) $(BUILT_SRCS:.c=.o) $(PARS_SRCS:.c=.o) $(STRUCT_SRCS:.c=.o) $(UTIL_SRCS:.c=.o)

HDR_DIR = includes

LIBFT_DIR = libft
LIBFT_FILE = libft.a
LIBFT = $(addprefix $(LIBFT_DIR)/,$(LIBFT_FILE))

CFLAGS = -Wall -Wextra -Werror
CC = cc $(CFLAGS) -g -I $(HDR_DIR)

BOLD = \033[1m
GRAY = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

%.o: %.c
	@$(CC) -c $< -o $@
	@echo "$(GRAY)Compiled: $<$(RESET)"

all: $(NAME)

$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Building executable...$(RESET)"
	@$(CC) -o $(NAME) $^ -lreadline
	@echo "$(GREEN)Executable $(NAME) successfully created!$(RESET)"
	@echo "$(BLUE)\n\
	█▀▄▀█ █ █▄░█ █ $(CYAN)█▀ █░█ █▀▀ █░░ █░░$(BLUE)\n\
	█░▀░█ █ █░▀█ █ $(CYAN)▄█ █▀█ ██▄ █▄▄ █▄▄$(RESET)\n"

clean:
	@echo "$(BLUE)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Cleaning complete!$(RESET)"

fclean: clean
	@echo "$(BLUE)Complete cleanup..."
	@rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Cleaning complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
