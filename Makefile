NAME = minishell

CC = cc -Wall -Wextra -Werror -g

INC = -I ./minishell.h

SRC_FILES = shell.c

SRC_DIR = ./src/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)

LIBFT_LIB = ./Libft/libft.a

LIBFT = ./Libft/

RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ)
	@echo "$(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)building files..$(RESET)"
	@$(CC) $(INC) $(SRC) -L./libft -lreadline -o $(NAME)
	@echo "$(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)executable created!$(RESET)"

$(LIBFT_LIB):
	@$(MAKE) -sC $(LIBFT)

clean:
	@$(MAKE) clean -sC $(LIBFT)
	@$(RM) $(OBJ)
	@echo "$(GREEN)Cleaning OK!$(RESET)"

fclean: clean
	$(MAKE) fclean -sC $(LIBFT)
	$(RM) $(NAME)
	@echo "$(GREEN)Fcleaning OK!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus


# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
RESET = \033[0m
