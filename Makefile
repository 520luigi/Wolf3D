# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szheng <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/27 20:34:54 by szheng            #+#    #+#              #
#    Updated: 2018/11/29 09:26:37 by szheng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

NAME = wolf3d

NOC		=	\033[0m
GREEN	=	\033[1;32m
YELLOW  =   \033[1;33m
BLUE	=	\033[1;34m
RED		=	\033[1;31m

SRCS = srcs/main.c srcs/color.c srcs/input_hooks.c srcs/move_loops.c \
       srcs/raycast.c srcs/read.c

INC = -I includes/fractol.h -I libft/

LIB = -L minilibx_macos/ -l mlx -L libft/ -lft

FRM = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	@mkdir -p obj/
	@make -C minilibx_macos
	@make -C libft
	@gcc -Wall -Werror -Wextra -c $(SRCS) $(INC)
	@mv *.o obj/
	@gcc obj/*.o $(LIB) -o $(NAME) $(FRM)
	@echo "$(GREEN)WOLF3D is ready to go!$(NOC)"
	@echo "$(YELLOW) \_/-.--.--.--.--.--."
	@echo ' (")__)__)__)__)__)__)'
	@echo '  ^ "" "" "" "" "" ""'

clean:
	@make -C minilibx_macos/ clean
	@make -C libft/ clean
	@rm -rf obj/
	@echo "$(BLUE)Removed Object files$(NOC)"

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo "$(RED)Removed Fractol executable$(NOC)"

re: fclean all
