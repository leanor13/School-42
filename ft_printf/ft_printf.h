/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:09:54 by yioffe            #+#    #+#             */
/*   Updated: 2023/11/01 11:14:34 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "libft/libft.h"

int	ft_printf(const char *str, ...);
int	ft_putptr(void *ptr);
int	ft_putnbr_hex(int n, char c);
int	ft_putnbr_u(unsigned int n);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putchar(char c);

#endif