NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INC = -I ./ -I /opt/homebrew/opt/readline/include
LDFLAGS = -L ./libft -L /opt/homebrew/opt/readline/lib
LDLIBS = -lft -lreadline

SRC_FILES = 

SRC_DIR = ./src/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)

LIBFT_LIB = ./libft/libft.a
LIBFT = ./libft/

RM = rm -rf

all: $(NAME)

$(LIBFT_LIB):
	@echo "Building libft in $(LIBFT)"
	@$(MAKE) -sC $(LIBFT)

$(NAME): $(LIBFT_LIB) $(OBJ)
	@echo "$(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)building files..$(RESET)"
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)$(BLINK)♥♥♥ minishell created! ♥♥♥$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@$(MAKE) clean -sC $(LIBFT)
	@$(RM) $(OBJ)
	@echo "$(GREEN)Cleaning OK!$(RESET)"

fclean: clean
	@$(MAKE) fclean -sC $(LIBFT)
	@$(RM) $(NAME)
	@echo "$(GREEN)Fcleaning OK!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus


# COLORS
RED		= \033[31m
CYAN	= \033[36m
BOLD	= \033[1m
BLUE	= \033[34m
GREEN	= \033[32m
BLINK	= \033[5m
RESET	= \033[0m
YELLOW	= \033[33m
MAGENTA	= \033[35m
