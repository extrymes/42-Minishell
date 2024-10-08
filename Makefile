NAME = minishell

EXEC_DIR = execution
BUILT_DIR = builtins
PARS_DIR = parsing
STRUCT_DIR = structs
UTIL_DIR = utils
BIN_DIR = bin

EXEC_FILES = pipex.c pipex_utils.c file_handler.c free_exec.c
BUILT_FILES = builtins.c pwd.c echo.c cd.c cd_utils.c env.c exit.c unset.c export.c export_utils.c export_utils2.c
PARS_FILES = tokenize.c input.c variables.c command.c prompt.c environment.c syntax.c metachars.c
STRUCT_FILES =  data.c entry.c token.c cmd.c arg.c file.c parse.c
UTIL_FILES =  signals.c events.c memory.c string.c error.c

SRCS = main.c \
	$(addprefix $(EXEC_DIR)/,$(EXEC_FILES)) \
	$(addprefix $(BUILT_DIR)/,$(BUILT_FILES)) \
	$(addprefix $(PARS_DIR)/,$(PARS_FILES)) \
	$(addprefix $(STRUCT_DIR)/,$(STRUCT_FILES)) \
	$(addprefix $(UTIL_DIR)/,$(UTIL_FILES))

OBJS = $(SRCS:%.c=$(BIN_DIR)/%.o)

LIBFT = libft/libft.a

INCLUDES = -I includes

CFLAGS = -Wall -Wextra -Werror -g
CC = cc $(CFLAGS)

BOLD = \033[1m
GRAY = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    RLFLAGS = -l readline
else ifeq ($(UNAME_S), Darwin)
    READLINE_DIR = $(shell brew --prefix readline)
    INCLUDES += -I $(READLINE_DIR)/include
    RLFLAGS = -L $(READLINE_DIR)/lib -l readline
else
    $(error Operating system not supported)
endif

all: $(LIBFT) $(NAME)

$(BIN_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -s -C libft
	@echo "$(GREEN)Building complete!$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@echo "\n$(YELLOW)Linking objects...$(RESET)"
	@$(CC) $(RLFLAGS) -o $(NAME) $^
	@echo "$(BLUE)Progress: 100%$(RESET)"
	@echo "$(GREEN)Compilation complete!$(RESET)"
	@echo "$(BLUE)\n\
	█▀▄▀█ █ █▄░█ █ $(CYAN)█▀ █░█ █▀▀ █░░ █░░$(BLUE)\n\
	█░▀░█ █ █░▀█ █ $(CYAN)▄█ █▀█ ██▄ █▄▄ █▄▄$(RESET)\n"

clean:
	@echo "$(BLUE)Cleaning objects...$(RESET)"
	@rm -rf $(BIN_DIR)
	@make clean -s -C libft
	@echo "$(GREEN)Cleaning complete!$(RESET)"

fclean: clean
	@echo "$(BLUE)Complete cleanup..."
	@rm -f $(NAME)
	@make fclean -s -C libft
	@echo "$(GREEN)Cleaning complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
