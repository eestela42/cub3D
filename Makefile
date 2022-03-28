# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 13:18:56 by user42            #+#    #+#              #
#    Updated: 2022/03/28 14:11:37 by maskedduck       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = clang
OPENGL = -lXext -lX11 -lbsd -lm
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -ISrcs 
-fsanitize=address

SRCS =	main.c				\
		parsing.c			\
		parsing_map.c		\
		parsing_map2.c		\
		point.c				\
		libft1.c			\
		fct_tab_ender.c		\
		fct_tab_sprites.c	\
		fct_tab_sprites2.c	\
		collision.c			\
		affichage_utils.c	\
		key_press.c			\
		point_utils.c		\
		affichage.c			

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