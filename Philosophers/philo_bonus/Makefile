NAME = philo_bonus

SRCS = $(addprefix srcs/,$(addsuffix .c, $(S)))
S = main utils clean init routines mutexes philo_actions threads

COMPRESS = ar rcs
RM = rm -f
CFLAGS = -O3 -Wall -Wextra -Werror -g3

CC = cc

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))

OBJS_DIR = objs

ifdef MACOS_CONFIG
	MAC_INFO = You are on macOS
else
	MAC_INFO = You are on School PC
endif

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

$(NAME): $(OBJS) 
	@echo "$(CYAN)Creating $(NAME) ..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "✅ $(GREEN)$(NAME) created $(NC)"

$(OBJS): includes/philo.h

clean:
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "✅ $(YELLOW) fclean done! $(NC)"

run: all
	./$(NAME)

re: fclean all

.PHONY: all fclean clean re
