NAME		=	cub3d
INC			=	inc
HEADER		=	-I inc
LIBFT		=	lib/libft/
# MINILIBX	=	./lib/mlx/
SRC_DIR		=	src/
OBJ_DIR		=	obj/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g
RM			=	rm -f
# MINILIBXCC	=	-I mlx -L ./lib/mlx/ -lmlx
# OPENGL		=	-framework OpenGL -framework AppKit

CUB_DIR		=	cub3d/
MAND_FILES	=	parse map_creation map_validation

UTIL_DIR	=	util/
UTIL_FILES	=	lines free

# BONUS_DIR	=	bonus/
# BONUS_FILES	=

SRC_FILES	=	$(addprefix $(CUB_DIR), $(MAND_FILES))
U_FILES	=	$(addprefix $(UTIL_DIR), $(UTIL_FILES))
# SRC_BFILES	=	$(addprefix $(BONUS_DIR), $(BONUS_FILES))

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

UTIL		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(U_FILES)))
UTIL_OBJ	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(U_FILES)))

# BSRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_BFILES)))
# BOBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_BFILES)))

OBJF		=	.cache_exists

all:			$(NAME)

$(NAME):		$(OBJ) $(UTIL_OBJ) $(OBJF)
				@make -C $(LIBFT)
				@cp lib/libft/libft.a .
				@$(CC) $(CFLAGS) $(OBJ) $(UTIL_OBJ) $(HEADER) libft.a -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(OBJF)
				@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJF):
				@mkdir -p $(OBJ_DIR)
				@mkdir -p $(OBJ_DIR)$(CUB_DIR)
				@mkdir -p $(OBJ_DIR)$(UTIL_DIR)
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
				@$(RM) -rf *.dSYM
				@find . -name ".DS_Store" -delete

# bonus:			$(BNAME)

# $(BNAME):		$(BOBJ)
#				@make -C $(LIBFT)
#				@cp lib/libft/libft.a .
#				@make -s -C $(MINILIBX)
#				@$(CC) $(CFLAGS) $(BSRC) $(HEADER) libft.a $(MINILIBXCC) $(OPENGL) -o $(BNAME)

re:				fclean all

.PHONY:			all clean fclean re
