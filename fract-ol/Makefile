NAME = fractol
BONUS_NAME = 

BONUS = $(addprefix bonus/,$(addsuffix .c, $(B)))
B = 

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = main fractal temp coloring hooks 

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))

BONUS_OBJS = $(addprefix $(OBJS_DIR_BONUS)/,$(BONUS:bonus/%.c=%.o))
OBJS_DIR = objs
OBJS_DIR_BONUS = objs_bonus

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

ifdef MACOS_CONFIG
	MLX_DIR = ./includes/minilibx-mac
	LDflags += -I$(MLX_DIR)
	LDflags += -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR = ./includes/minilibx-linux
	LDflags += -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

MLX = $(MLX_DIR)/libmlx.a

LIBS = $(LIBFT)

all: $(NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR_BONUS)/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBS) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LDflags)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS) $(LDflags)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@echo $(MLX) compiled and ready!

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJS_DIR_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

run: all
	./$(NAME) 

re: fclean all

.PHONY: all fclean clean re
