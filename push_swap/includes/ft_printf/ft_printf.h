/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:09:54 by yioffe            #+#    #+#             */
/*   Updated: 2023/11/02 12:16:22 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# ifndef HEX_LOW
#  define HEX_LOW "0123456789abcdef"
# endif

# ifndef HEX_UP
#  define HEX_UP "0123456789ABCDEF"
# endif

# ifndef DEC
#  define DEC "0123456789"
# endif

# ifndef BONUS_FLAGS
#  define BONUS_FLAGS "# +"
# endif

int	ft_printf(const char *str, ...);
int	ft_nbr(long long n, char *base, char type);
int	ft_putstr(char *s);
int	ft_putchar(char c);

#endif