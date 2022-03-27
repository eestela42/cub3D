# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 13:18:56 by user42            #+#    #+#              #
#    Updated: 2022/03/27 15:47:00 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = clang
OPENGL = -lXext -lX11 -lbsd -lm
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -ISrcs -fsanitize=address

SRCS =	main.c				\
		parsing.c			\
		parsing_map.c		\
		point.c				\
		libft1.c			\
		fct_tab_ender.c		\
		fct_tab_sprites.c

OBJS = ${addprefix srcs/,${SRCS:.c=.o}}

all:	$(NAME)

$(NAME):	$(OBJS)
		make -C minilibx-linux
		$(CC)  $(OBJS) $(CFLAGS) -o $(NAME) minilibx-linux/libmlx.a $(OPENGL)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

po: all clean

.PHONY:	all  clean fclean re