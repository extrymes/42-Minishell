NAME = libft.a

BIN_DIR = bin

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_isspace.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memmove.c ft_strcpy.c ft_strlcpy.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c \
	ft_strchr.c ft_strstr.c ft_strrchr.c \
	ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
	ft_strnstr.c ft_atoi.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:%.c=$(BIN_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror  -g
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

$(BIN_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -rf $(BIN_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
