# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thberrid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/29 19:26:47 by thberrid          #+#    #+#              #
#    Updated: 2019/11/13 05:32:42 by thberrid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL	= /bin/sh
NAME	= fdf
DIR_C 	= srcs
DIR_O	= obj
DIR_H	= includes
NAME_C	= main.c
NAME_O	= $(NAME_C:.c=.o)
FILES_C	= $(addprefix $(DIR_C)/, $(NAME_C))
FILES_O	= $(addprefix $(DIR_O)/, $(NAME_O))
FILES_H	= fdf.h
LIBFT	= ./libft/libft.a
MLX		= ./libmlx.dylib
FLAGS	= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(FILES_O) $(DIR_H)/$(FILES_H) $(LIBFT) $(MLX)
	gcc -I ./$(DIR_H) -I ./libft/includes -I ./minilibx/ -L ./libft/ -lft $(MLX) -o $(NAME) $(FILES_O)
 
$(DIR_O)/%.o : $(DIR_C)/%.c $(DIR_H)/$(FILES_H)
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
