# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 15:22:58 by zoulhafi          #+#    #+#              #
#    Updated: 2019/02/08 12:21:30 by zoulhafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
PATH_INCLUDES = includes/
LIBFT_INCLUDES = libft/includes/
DEPS = includes/const.h includes/ft_select.h libft/includes/libft.h
FLAGS = -Wall -Wextra -Werror
PATH_SRCS = srcs/
_SRCS = ft_select.c init_terms.c args.c draw.c cursor.c cursor2.c
SRCS = $(patsubst %.c, $(PATH_SRCS)%.c, $(_SRCS))
OBJS = $(patsubst %.c, %.o, $(_SRCS))

all: $(NAME)

$(NAME): $(DEPS)
	make -C libft re
	gcc $(FLAGS) -c $(SRCS) -I $(PATH_INCLUDES) -I $(LIBFT_INCLUDES)
	gcc $(FLAGS) -o $(NAME) $(OBJS) -l termcap -L libft -lft

clean:
	make -C libft clean
	rm -Rf $(OBJS)

fclean: clean
	make -C libft fclean
	rm -Rf $(NAME)

re: fclean all
