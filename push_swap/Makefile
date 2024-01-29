NAME = push_swap
BONUS_NAME = checker

BONUS = $(addprefix bonus/,$(addsuffix .c, $(B)))
B = 

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = main input_validation list_tools swap_helper swap_operations ft_atoi_custom

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3
CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))

BONUS_OBJS = $(addprefix $(OBJS_DIR_BONUS)/,$(BONUS:bonus/%.c=%.o))
OBJS_DIR = objs
OBJS_DIR_BONUS = objs_bonus

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ./includes/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

LIBS = $(LIBFT) $(PRINTF)

TEST_SRC = $(addprefix tests/,$(addsuffix .c, $(T)))
T = test_input_validation test_push_swap test_list_tools test_swap_helper
TEST_OBJ = $(addprefix $(OBJS_DIR)/, $(notdir $(TEST_SRC:.c=.o)))
TEST_NAME = run_tests

all: $(NAME) 
bonus: $(BONUS_NAME)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR_BONUS)/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: tests/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(PRINTF):
	@$(MAKE) -C $(PRINTF_DIR) --no-print-directory

$(TEST_NAME): $(TEST_OBJ) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)
	@$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_OBJ) $(filter-out $(OBJS_DIR)/main.o, $(OBJS)) $(LIBS)

test: $(TEST_NAME)
	./$(TEST_NAME)

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJS_DIR_BONUS)
	@$(RM) $(TEST_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(PRINTF_DIR) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(PRINTF_DIR) fclean --no-print-directory

run: all
	./$(NAME) 

re: fclean all

.PHONY: all fclean clean re test