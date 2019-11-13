# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thberrid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 03:18:51 by thberrid          #+#    #+#              #
#    Updated: 2019/11/13 03:19:44 by thberrid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thberrid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/29 19:26:47 by thberrid          #+#    #+#              #
#    Updated: 2019/10/06 06:02:08 by thberrid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh
NAME = fdf
DIR_C = srcs
DIR_O = obj
DIR_H = includes
NAME_C = main.c
NAME_O = $(NAME_C:.c=.o)
FILES_C = $(addprefix $(DIR_C)/, $(NAME_C))
FILES_O = $(addprefix $(DIR_O)/, $(NAME_O))
FILES_H = fdf.h
LIBFT = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(FILES_O) $(DIR_H)/$(FILES_H) $(LIBFT)
	gcc -I ./$(DIR_H) -I ./libft/ -L ./libft/ -lft -o $(NAME) $(FILES_O)
 
$(DIR_O)/%.o : $(DIR_C)/%.c $(DIR_H)/$(FILES_H)
	@ mkdir -p $(DIR_O)
	gcc -I ./$(DIR_H) $(FLAGS) -I ./libft/ -c -o $@ $<

$(LIBFT) :
	make -C ./libft/

.PHONY : clean
clean :
	rm -f $(FILES_O)
	make -C ./libft fclean

.PHONY : fclean
fclean : clean
	rm -f $(NAME)

.PHONY : re
re : fclean all
