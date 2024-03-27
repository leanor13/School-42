NAME = fractol

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = main color_schemas hook_functions exit_and_free read_input instructions fractal_init \
	fractal_coloring movement

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -O3 -Wall -Wextra -Werror -g3
CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))

OBJS_DIR = objs

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

$(NAME): $(OBJS) $(LIBS) $(MLX)
	@echo "$(CYAN)Creating $(NAME) ..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LDflags)
	@echo "✅ $(GREEN)$(NAME) created $(NC)"

$(OBJS): includes/fractol.h

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@echo "$(CYAN)Creating $(MLX) ..."
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@echo "✅ $(GREEN)$(MLX) compiled and ready! $(NC)"

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null
	@echo "✅ $(YELLOW) fclean done! $(NC)"

run: all
	./$(NAME) m

norminette:
	norminette $(LIBFT_DIR)
	norminette $(SRCS)
	norminette includes/*.*

re: fclean all

.PHONY: all fclean clean re norminette
