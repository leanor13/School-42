/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:52:11 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/25 16:39:26 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	input_instruction(void)
{
	ft_putstr_fd("                    Instruction:\n", STDERR_FILENO);
	ft_putstr_fd("1. Choose fractal type (mandatory):\n", STDERR_FILENO);
	ft_putstr_fd("    - For Mandelbrot set send 'm' or 'Mandelbrot'\n", STDERR_FILENO);
	ft_putstr_fd("    - For Julia set send 'j' or 'Julia', and then (optional) 2 double values in format: xx.xx and yy.yy. Both values should be in range (-2.0, 2.0)\n", STDERR_FILENO);
	ft_putstr_fd("    - For Tricorn set send 't' or 'Tricorn'\n", STDERR_FILENO);
	ft_putstr_fd("2. Adjust iteration number (optional):\n", STDERR_FILENO);
	ft_putstr_fd("    If you wish to adjust number of iterations, send i_xxx, where x is digit. Example: i_100, maximum i_999, minimum i_2\n", STDERR_FILENO);
	ft_putstr_fd("    High iterations number may and wil cause slowness of the program\n", STDERR_FILENO);
	ft_putstr_fd("    Default iteration number is i_500, applied automatically\n", STDERR_FILENO);
	ft_putstr_fd("All additional parameters will be ignored\n", STDERR_FILENO);
	ft_putstr_fd("                    Have fun!\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	in_window_usage(void)
{
	ft_putstr_fd("                    Keys:\n", STDERR_FILENO);
	ft_putstr_fd("1. Zoom in and zoom: use mouse wheel\n", STDERR_FILENO);
	ft_putstr_fd("2. Move fractal: use arrow keys\n", STDERR_FILENO);
	ft_putstr_fd("3. Change color scheme: press 1, 2 or 3\n", STDERR_FILENO);
	ft_putstr_fd("4. Change Julia constant on a flow: press r for real part change, i for imaginary part change\n", STDERR_FILENO);
	ft_putstr_fd("All additional buttons will be ignored\n", STDERR_FILENO);
}