NAME = minishell

SRCS = main.c

EXEC_DIR = execution
EXEC_FILES = pipex.c pipex_utils.c
EXEC_SRCS = $(addprefix $(EXEC_DIR)/,$(EXEC_FILES))

PARS_DIR = parsing
PARS_FILES = env.c prompt.c input.c input_utils.c
PARS_SRCS = $(addprefix $(PARS_DIR)/,$(PARS_FILES))

UTIL_DIR = utils
UTIL_FILES =  data.c entry.c cmd.c flag.c realloc.c strjoin_free.c error.c
UTIL_SRCS = $(addprefix $(UTIL_DIR)/,$(UTIL_FILES))

OBJS = $(SRCS:.c=.o) $(PARS_SRCS:.c=.o) $(UTIL_SRCS:.c=.o)

HDR_DIR = includes

LIBFT_DIR = libft
LIBFT_FILE = libft.a
LIBFT = $(addprefix $(LIBFT_DIR)/,$(LIBFT_FILE))

CFLAGS = -Wall -Wextra -Werror
CC = cc $(CFLAGS) -g -I $(HDR_DIR)

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
