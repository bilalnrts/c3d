NAME		=	cub3d
INC			=	inc
HEADER		=	-I inc
LIBFT		=	lib/libft/
MINILIBX	=	lib/mlx/
SRC_DIR		=	src/
OBJ_DIR		=	obj/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g
RM			=	rm -f
OPENGL		=	-framework OpenGL -framework AppKit

CUB_DIR		=	cub3d/
MAND_NAMES	=	parse map_creation map_validation set_width \
				map_validation2 player set_colors set_textures

UTIL_DIR	=	util/
UTIL_NAMES	=	lines free

MLX_DIR		=	mlx_process/
MLX_NAMES	=	keyboard_interaction mlx_init

PLAY_DIR	=	play/
PLAY_NAMES	=	move

RAY_DIR		=	raycast/
RAY_NAMES	=	casting drawing

SRC_FILES	=	$(addprefix $(CUB_DIR), $(MAND_NAMES))
UTIL_FILES	=	$(addprefix $(UTIL_DIR), $(UTIL_NAMES))
MLX_FILES	=	$(addprefix $(MLX_DIR), $(MLX_NAMES))
PLAY_FILES	=	$(addprefix $(PLAY_DIR), $(PLAY_NAMES))
RAY_FILES	=	$(addprefix $(RAY_DIR), $(RAY_NAMES))

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

UTIL		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(UTIL_FILES)))
UTIL_OBJ	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(UTIL_FILES)))

MLX			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(MLX_FILES)))
MLX_OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(MLX_FILES)))

PLAY		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(PLAY_FILES)))
PLAY_OBJ	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(PLAY_FILES)))

RAY			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(RAY_FILES)))
RAY_OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(RAY_FILES)))

OBJF		=	.cache_exists

all:			$(NAME)

$(NAME):		$(OBJ) $(UTIL_OBJ) $(MLX_OBJ) $(PLAY_OBJ) $(RAY_OBJ) $(OBJF)
				@make -C $(LIBFT)
				@cp lib/libft/libft.a .
				@make -C $(MINILIBX)
				@cp lib/mlx/libmlx.a .
				@$(CC) $(CFLAGS) $(OBJ) $(UTIL_OBJ) $(MLX_OBJ) $(PLAY_OBJ) $(RAY_OBJ) $(HEADER) $(OPENGL) libft.a libmlx.a -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(OBJF)
				@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJF):
				@mkdir -p $(OBJ_DIR)
				@mkdir -p $(OBJ_DIR)$(CUB_DIR)
				@mkdir -p $(OBJ_DIR)$(UTIL_DIR)
				@mkdir -p $(OBJ_DIR)$(MLX_DIR)
				@mkdir -p $(OBJ_DIR)$(PLAY_DIR)
				@mkdir -p $(OBJ_DIR)$(RAY_DIR)
				@touch $(OBJF)

clean:
				@$(RM) -r $(OBJ_DIR)
				@make clean -C $(LIBFT)
				@$(RM) $(OBJF)


fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(BNAME)
				@$(RM) libft.a
				@$(RM) $(LIBFT)/libft.a
				@$(RM) libmlx.a
				@$(RM) $(MINILIBX)/libmlx.a
				@$(RM) -rf *.dSYM
				@find . -name ".DS_Store" -delete

re:				fclean all

.PHONY:			all clean fclean re
