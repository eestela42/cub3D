# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 13:18:56 by user42            #+#    #+#              #
#    Updated: 2022/03/29 19:53:22 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus
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
OBJS_BONUS = ${addprefix srcs_bonus/,${SRCS:.c=.o}}

all:	$(NAME)

$(NAME):	$(OBJS)
		make -C minilibx-linux
		$(CC)  $(OBJS) $(CFLAGS) -o $(NAME) minilibx-linux/libmlx.a $(OPENGL)

bonus: $(OBJS_BONUS)
		make -C minilibx-linux
		$(CC)  $(OBJS_BONUS) $(CFLAGS) -o $(NAME) minilibx-linux/libmlx.a $(OPENGL)

clean:
		rm -f $(OBJS)
		rm -f $(OBJS_BONUS)

fclean: clean
		rm -f $(NAME)
		rm -f $(NAME_BONUS)

re:		fclean all

po: all clean

bonus_po : bonus clean

.PHONY:	all bonus clean fclean re po bonus_po