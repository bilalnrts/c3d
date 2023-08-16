NAME			=	libft.a
CC				=	gcc
CCFLAG			=	-Wall -Wextra -Werror -I
INCLUDE			=	inc/
SRC_DIR			=	src/
OBJ_DIR			=	obj/
RM				=	rm -f
AR				=	ar rcs

FTIS_DIR		=	ft_is/
FTIS_FILES		=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint

FTLST_DIR		=	ft_lst/
FTLST_FILES		=	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
					ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

FTMEM_DIR		=	ft_mem/
FTMEM_FILES		=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset

PRINTF_DIR		=	ft_printf/
PRINTF_FILES	=	ft_printf ft_printf_utils

FTPUT_DIR		=	ft_put/
FTPUT_FILES		=	ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTSTR_DIR		=	ft_str/
FTSTR_FILES		=	ft_split ft_strchr ft_strcmp ft_strdup ft_striteri ft_strjoin \
					ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr \
					ft_strrchr ft_strtrim ft_substr

FTTO_DIR		=	ft_to/
FTTO_FILES		=	ft_atoi ft_itoa ft_tolower ft_toupper

GNL_DIR			=	gnl/
GNL_FILES		=	get_next_line get_next_line_utils

SRC_FILES		+=	$(addprefix $(FTIS_DIR), $(FTIS_FILES))
SRC_FILES		+=	$(addprefix $(FTLST_DIR), $(FTLST_FILES))
SRC_FILES		+=	$(addprefix $(FTMEM_DIR), $(FTMEM_FILES))
SRC_FILES		+=	$(addprefix $(PRINTF_DIR), $(PRINTF_FILES))
SRC_FILES		+=	$(addprefix $(FTPUT_DIR), $(FTPUT_FILES))
SRC_FILES		+=	$(addprefix $(FTSTR_DIR), $(FTSTR_FILES))
SRC_FILES		+=	$(addprefix $(FTTO_DIR), $(FTTO_FILES))
SRC_FILES		+=	$(addprefix $(GNL_DIR), $(GNL_FILES))

SRC				=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ				=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF			=	.cache_exists

all				:	$(NAME)

$(NAME)			:	$(OBJ)
					@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJF)
					@$(CC) $(CCFLAG) $(INCLUDE) -c $< -o $@

$(OBJF)			:
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(FTIS_DIR)
					@mkdir -p $(OBJ_DIR)$(FTMEM_DIR)
					@mkdir -p $(OBJ_DIR)$(FTLST_DIR)
					@mkdir -p $(OBJ_DIR)$(PRINTF_DIR)
					@mkdir -p $(OBJ_DIR)$(FTPUT_DIR)
					@mkdir -p $(OBJ_DIR)$(FTTO_DIR)
					@mkdir -p $(OBJ_DIR)$(FTSTR_DIR)
					@mkdir -p $(OBJ_DIR)$(GNL_DIR)
					@touch $(OBJF)

clean			:
					@$(RM) -r $(OBJ_DIR)
					@$(RM) $(OBJF)

fclean			:	clean
					@$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re

