# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mservais <mservais@student.s19.be >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 13:54:56 by mservais          #+#    #+#              #
#    Updated: 2022/01/18 19:12:10 by mservais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES		=	main.c							\
					0_memory_management/free.c		\
					0_memory_management/init.c		\
					1_parsing/check_content.c		\
					1_parsing/check_map.c			\
					1_parsing/parse_file.c			\
					1_parsing/utils.c				\
					2_game_dynamics/controls.c		\
					2_game_dynamics/draw.c		\

OBJ_FILES		=	$(SRC_FILES:.c=.o)

NAME			= 	cub3d

CUB3D_LIB		=	libcub3d.a

MLX_LIB			=	libmlx.dylib

CC				=	gcc

INCLUDE			=	-Lmlx -lmlx -framework OpenGL -framework AppKit -fsanitize=address

CFLAGS			=	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -s -C mlx
	cp mlx/$(MLX_LIB) $(MLX_LIB)
	@$(MAKE) -s -C get_next_line
	cp get_next_line/libgnl.a $(CUB3D_LIB)
	ar -rcs $(CUB3D_LIB) $^
	$(CC) $(CFLAGS) main.c $(CUB3D_LIB) $(INCLUDE) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJ_FILES)
	$(MAKE) clean -C get_next_line
	$(MAKE) clean -C mlx

fclean: clean
	rm -rf $(NAME)
	rm -rf $(CUB3D_LIB)
	rm -rf $(MLX_LIB)
	$(MAKE) fclean -C get_next_line

re: fclean all

.PHONY: all clean fclean re