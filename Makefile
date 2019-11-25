# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thberrid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/29 19:26:47 by thberrid          #+#    #+#              #
#    Updated: 2019/11/25 02:12:26 by thberrid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL	= /bin/sh
NAME	= fdf
DIR_C 	= srcs
DIR_O	= obj
DIR_H	= includes
NAME_C	= main.c \
		  colors.c \
		  image.c \
		  map_parse.c \
		  map_print.c \
		  matrix.c \
		  matrix_addrow.c \
		  matrix_free.c \
		  projection_persp.c \
		  vertex.c
NAME_O	= $(NAME_C:.c=.o)
NAME_H	= fdf.h \
		  keycodes.h
FILES_C	= $(addprefix $(DIR_C)/, $(NAME_C))
FILES_O	= $(addprefix $(DIR_O)/, $(NAME_O))
FILES_H	= $(addprefix $(DIR_H)/, $(NAME_H))
LIBFT	= ./libft/libft.a
MLX		= ./libmlx.dylib
FLAGS	= -Wall -Wextra -Werror -g

all : $(NAME)

$(NAME) : $(FILES_O) $(FILES_H) $(LIBFT) $(MLX)
	gcc -I ./$(DIR_H) -I ./libft/includes -I ./minilibx/ -L ./libft/ -lft $(MLX) -o $(NAME) $(FILES_O)
 
$(DIR_O)/%.o : $(DIR_C)/%.c $(FILES_H)
	@ mkdir -p $(DIR_O)
	gcc $(FLAGS) -I ./$(DIR_H) -I ./libft/includes -I ./minilibx -c -o $@ $<

$(LIBFT) :
	make -C ./libft/

$(MLX) :
	make -C ./minilibx/
	cp ./minilibx/libmlx.dylib libmlx.dylib

.PHONY : clean
clean :
	rm -f $(FILES_O)
	make -C ./libft fclean
	make -C ./minilibx clean

.PHONY : fclean
fclean : clean
	rm -f $(NAME)

.PHONY : re
re : fclean all
