# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 19:28:24 by yioffe            #+#    #+#              #
#    Updated: 2023/10/19 13:39:18 by yioffe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c ft_putnbr_hex.c ft_putnbr_u.c ft_putptr.c \
	ft_putchar.c ft_putnbr.c ft_putstr.c
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_MAKE = $(MAKE) -C $(LIBFT_DIR)

# Rules
# .PHONY: all clean fclean re fcleanall

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

# $(OBJS): %.o: %.c
# 	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(LIBFT_MAKE) clean

fclean: clean
	$(RM) $(NAME)
	$(LIBFT_MAKE) fclean

re: fclean all

$(LIBFT):
	$(LIBFT_MAKE)

.PHONY: all clean fclean re fcleanall