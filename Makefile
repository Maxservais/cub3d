
SRC_FILES		=	main.c							\
					0_memory_management/free.c		\
					0_memory_management/init.c		\
					1_parsing/check_content.c		\
					1_parsing/check_map.c			\
					1_parsing/parse_file.c			\
					1_parsing/utils.c				\
					2_game_dynamics/controls.c		\
					2_game_dynamics/draw_game.c		\
					2_game_dynamics/draw_minimap.c	\
					2_game_dynamics/raycaster.c		\
					2_game_dynamics/utils.c			\

OBJ_FILES		=	$(SRC_FILES:.c=.o)

NAME			= 	cub3d

CUB3D_LIB		=	libcub3d.a

LIBFT_LIB		=	libft.a

MLX_LIB			=	libmlx.a

CC				=	gcc

INCLUDE			=	-lmlx -framework OpenGL -framework AppKit -fsanitize=address -g

CFLAGS			=	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -s -C libft
	@cp libft/libft.a .
	@$(MAKE) -s -C mlx
	cp mlx/$(MLX_LIB) $(MLX_LIB)
	@$(MAKE) -s -C get_next_line
	cp get_next_line/libgnl.a $(CUB3D_LIB)
	ar -rcs $(CUB3D_LIB) $^
	$(CC) $(CFLAGS) main.c $(LIBFT_LIB) $(CUB3D_LIB) $(INCLUDE) -o $(NAME)

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
	rm -rf $(LIBFT_LIB)
	$(MAKE) fclean -C get_next_line

re: fclean all

.PHONY: all clean fclean re
