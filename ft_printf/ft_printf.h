/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:09:54 by yioffe            #+#    #+#             */
/*   Updated: 2023/11/01 13:33:49 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
//# include "libft/libft.h"

# ifndef MIN
#  define MIN -2147483648
# endif

# ifndef HEX_LOW
#  define HEX_LOW "0123456789abcdef"
# endif

# ifndef HEX_UP
#  define HEX_UP "0123456789ABCDEF"
# endif

# ifndef DEC
#  define DEC "0123456789"
# endif

int	ft_printf(const char *str, ...);
int	ft_nbr(long long n, char *base, char type);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putchar(char c);
int	ft_strlen(const char *str);

#endif