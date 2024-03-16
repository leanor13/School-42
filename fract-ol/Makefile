NAME = fractol
BONUS_NAME =

BONUS = $(addprefix bonus/,$(addsuffix .c, $(B)))
B =

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = main

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3
LDflags = -I/usr/include -Imlx_linux -O3
CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))

BONUS_OBJS = $(addprefix $(OBJS_DIR_BONUS)/,$(BONUS:bonus/%.c=%.o))
OBJS_DIR = objs
OBJS_DIR_BONUS = objs_bonus

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./includes/Minilibx
MLX = $(MLX_DIR)/libmlx.a -lXext -lX11 -lm

LIBS = $(LIBFT)

all: $(NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDflags) -c $< -o $@

$(OBJS_DIR_BONUS)/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDflags) -c $< -o $@

$(NAME): $(OBJS) $(LIBS) $(MLX)
	@$(CC) $(LDflags) -o $(NAME) $(OBJS) $(LIBS) $(MLX)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBS)
	@$(CC) $(CFLAGS) $(LDflags) -o $(BONUS_NAME) $(BONUS_OBJS) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)

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
