NAME = fractol
BONUS_NAME = 

BONUS = $(addprefix srcs/,$(addsuffix .c, $(B)))
B = 

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = main fractal coloring hooks my_mlx julia

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -O3 -Wall -Wextra -Werror -g
CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))

BONUS_OBJS = $(addprefix $(OBJS_DIR_BONUS)/,$(BONUS:bonus/%.c=%.o))
OBJS_DIR = objs
OBJS_DIR_BONUS = objs_bonus

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

ifdef MACOS_CONFIG
	MAC_INFO = You are on macOS
	MLX_DIR = ./includes/minilibx-mac
	LDflags += -I$(MLX_DIR)
	LDflags += -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MAC_INFO = You are on School PC
	MLX_DIR = ./includes/minilibx-linux
	LDflags += -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

MLX = $(MLX_DIR)/libmlx.a

LIBS = $(LIBFT)

GREEN = \033[0;32m
CYAN = \033[0;36m
PURPLE = \033[0;35m
YELLOW = \033[0;33m
NC = \033[0m

$(info $(MAC_INFO))

all: $(NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR_BONUS)/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBS) $(MLX)
	@echo "$(CYAN)Creating $(NAME) ..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LDflags)
	@echo "✅ $(GREEN)$(NAME) created"

$(OBJS): includes/fractol.h

$(BONUS_NAME): $(BONUS_OBJS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS) $(LDflags)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@echo "$(CYAN)Creating $(MLX) ..."
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@echo "✅ $(GREEN)$(MLX) compiled and ready!"

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJS_DIR_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null
	@echo "✅ $(YELLOW) fclean done!"

run: all
	./$(NAME) 

re: fclean all

.PHONY: all fclean clean re
