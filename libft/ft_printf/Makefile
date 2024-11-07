# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 14:06:36 by jmaruffy          #+#    #+#              #
#    Updated: 2024/06/20 14:44:42 by jmaruffy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

FLAGS	= -Wall -Werror -Wall

SRCS	= ft_printf.c\
		utility_ft.c\

OBJS	= $(SRCS:.c=.o)

CC		= gcc

all		: $(NAME)

$(NAME): $(OBJS)
		ar crs $@ $(OBJS)

.c.o:
		cc $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
