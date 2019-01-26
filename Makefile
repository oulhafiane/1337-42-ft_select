# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 15:22:58 by zoulhafi          #+#    #+#              #
#    Updated: 2019/01/26 15:34:17 by zoulhafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
PATH_INCLUDES = includes/
LIBFT_INCLUDES = libft/includes/
DEPS = includes/ft_select.h libft/includes/libft.h
FLAGS = -Wall -Wextra -Werror
SRCS = ft_select.c
PATH_SRCS = srcs/
OBJS = $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

$(NAME): $(DEPS)
	make -C libft re
	gcc $(FLAGS) -c $(PATH_SRCS)$(SRCS) -I $(PATH_INCLUDES) -I $(LIBFT_INCLUDES)
	gcc $(FLAGS) -o $(NAME) $(OBJS) -L libft -lft

clean:
	make -C libft clean
	rm -Rf $(OBJS)

fclean: clean
	make -C libft fclean
	rm -Rf $(NAME)

re: fclean all
