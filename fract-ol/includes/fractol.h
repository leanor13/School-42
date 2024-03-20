/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/20 22:23:03 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

#ifdef __APPLE__
# include "minilibx-mac/mlx.h"
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define LEFT 123
# define RIGHT 124
# define DOWN 125

#else
# include "minilibx-linux/mlx.h"
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define RIGHT 65363
# define DOWN 65364
#endif

#define NUM_RAINBOW_COLORS 7
extern int my_rainbow_colors[NUM_RAINBOW_COLORS];

enum 
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/* movement constants*/
#define ZOOM_IN 1.1
#define ZOOM_OUT 0.9
#define MOVE_STEP 0.1


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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct fractal
{
	t_data	img;
	t_vars	vars;
	t_pixel	pix_max;
	t_point	min_bound;
	t_point	max_bound;
	int		iter;
	
}	t_fractal;


/* Mandelbrot fractal */
t_complex	mandelbrot_iter(t_complex c, t_complex c_0);

/* basic img functions */
void		my_mlx_pixel_put(t_data *data, t_pixel pixel, int color);
t_complex	my_map_pixel(t_pixel pixel, t_point min_bound, t_point max_bound, t_pixel pix_max);

/* build fractal */
t_fractal	*init_fractal(t_pixel pix_max,  t_point min_bound, t_point max_bound, int iter);
void		draw_fractal(t_fractal *f);
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