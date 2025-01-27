NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INC = -I ./ -I /opt/homebrew/opt/readline/include
LDFLAGS = -L ./libft -L /opt/homebrew/opt/readline/lib
LDLIBS = -lft -lreadline

SRC_FILES = main.c\
			/builtins/ft_cd.c\
			/builtins/ft_echo.c\
			/builtins/ft_env.c\
			/builtins/ft_exit.c\
			/builtins/ft_export.c\
			/builtins/ft_pwd.c\
			/builtins/ft_unset.c\
			/env/env.c\
			/env/env_utils.c\
			/token/token_commands.c\
			/token/token_specials.c\
			/token/token_utils.c\
			/token/token_words.c\
			/cleaning/free.c\
			/cleaning/free_env.c\
			/cleaning/exit.c\
			/parsing/parser.c\
			/parsing/ast.c\
			/parsing/ast_utils.c\
			/parsing/parsing_utils.c\
			/parsing/redirections.c\
			/parsing/ast_builder.c\
			/lexer/lexer.c\
			/lexer/get_next_token.c\
			/signals/signal.c\
			/signals/signal_utils.c\
			/expansion/exp.c\
			/expansion/exp_utils.c\
			/expansion/exp_wildcards.c\
			/expansion/exp_var.c\
			/expansion/exp_arg_utils.c\
			/expansion/exp_filename.c\
			/expansion/exp_filename_utils.c\
			/exec/exec.c\
			/exec/heredoc_utils.c\
			/exec/heredoc.c\
			/exec/exec_logical.c\
			/exec/exec_pipeline.c\
			/exec/exec_pipeline_utils.c\
			/exec/exec_redirection.c\
			/exec/exec_subshell.c\
			/exec/exec_command.c\
			/exec/exec_command_utils.c\

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
	@echo "$(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)$(BLINK)minishell created!$(RESET)"

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
