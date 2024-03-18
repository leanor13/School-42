/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/18 22:27:51 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include <math.h>
# include <stdio.h>

#ifdef __APPLE__
# include "minilibx-mac/mlx.h"
#else
# include "minilibx-linux/mlx.h"
#endif

#define NUM_RAINBOW_COLORS 7

/* int rainbow_colors[NUM_RAINBOW_COLORS] = {
    0xFF0000, // Red
    0xFF7F00, // Orange
    0xFFFF00, // Yellow
    0x00FF00, // Green
    0x0000FF, // Blue
    0x4B0082, // Indigo
    0x9400D3  // Violet
}; */

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct pixel
{
	int	x;
	int	y;
}	t_pixel;

typedef struct point
{
	double	x;
	double	y;
}	t_point;

typedef struct complex
{
	double	real;
	double	imaginary;
}	t_complex;

/* Mandelbrot fractal */
t_complex	mandelbrot_iter(t_complex c, t_complex c_0);

/* basic img functions */
void		my_mlx_pixel_put(t_data *data, t_pixel pixel, int color);
t_complex	my_map_pixel(t_pixel pixel, t_point min_bound, t_point max_bound, t_pixel pix_max);

/* build fractal */
void		color_pixel(t_data *img, t_point min_bound, t_point max_bound, 
	t_pixel pix_max, t_pixel pixel, int max_iter);
void		color_all_pixels(t_data *img, t_point min_bound, t_point max_bound, 
	t_pixel pix_max, int max_iter);

/* coloring schemas */
int 		map_color_general(int iter);
int 		map_color_maxiter(int iter, int max_iter);
int 		map_color_maxiter2(int iter, int max_iter);

// temp and test
void		my_mlx_horizontal_line_put(t_data *data, t_pixel start, int len, int color);
void		my_mlx_vertical_line_put(t_data *data, t_pixel start, int len, int color);
t_pixel 	map_coordinate_to_pixel(t_complex coord, t_point min_bound, t_point max_bound, t_pixel pix_max);
void		print_mapped_complex_numbers(t_point min_bound, t_point max_bound, t_pixel pix_max);
t_complex	my_map_pixel(t_pixel pixel, t_point min_bound, t_point max_bound, t_pixel pix_max);

#endif