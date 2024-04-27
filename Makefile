NAME		:= fractol

# norminette error
INC			:= $(shell find . -name "*.h" -exec dirname {} \; | sort -u | sed 's/^/-I /' | tr '\n' ' ')

SRCS_DIR	:= ./srcs

# norminette error
SRCS		:= $(shell find . -name "*.c" | grep -v mlx | tr '\n' ' ')

OBJS_DIR	:= ./objs
OBJS		:= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))
DEPS		:= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.d))

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror $(INC) -MMD -MP 

# Debug
ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -DDEBUG
endif

ifeq ($(MAKECMDGOALS), address)
	CFLAGS += -g3 -fsanitize=address
endif

all			: $(NAME)

$(NAME)	: $(OBJS)
	$(MAKE) -C ./mlx
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./mlx -lmlx -framework OpenGL -framework AppKit

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean		:
	make -C ./mlx clean
	rm -rf $(OBJS_DIR)

fclean		: clean
	make -C ./mlx fclean
	$(RM) $(NAME)

re			: fclean all

debug		: re

address		: re

norm		:
	norminette srcs includes

.PHONY		: all clean fclean re debug address

-include $(DEPS)
