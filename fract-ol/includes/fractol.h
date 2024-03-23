/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/23 17:38:58 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "error_handling.h"
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

# ifdef __APPLE__
#  include "minilibx-mac/mlx.h"
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define UP 126
#  define LEFT 123
#  define RIGHT 124
#  define DOWN 125

# else
#  include "minilibx-linux/mlx.h"
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define UP 65362
#  define LEFT 65361
#  define RIGHT 65363
#  define DOWN 65364
# endif

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
# define ZOOM_IN 1.1
# define ZOOM_OUT 0.9
# define MOVE_STEP 0.1

typedef struct s_data
{
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

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct fractal
{
	t_data	*img;
	void	*mlx;
	void	*win;
	t_pixel	pix_max;
	t_point	min_bound;
	t_point	max_bound;
	int		iter;

}	t_fractal;

/* fract constants */
# define MIN_BOUND	(t_point){-2, -2}
# define MAX_BOUND	(t_point){2, 2}
# define MAX_PIX	(t_pixel){800, 800}
# define MAX_ITER	100

/* Mandelbrot fractal */
t_point	mandelbrot_iter(t_point c, t_point c_0);

/* basic img functions */
void		my_mlx_pixel_put(t_data *data, t_pixel pixel, int color);
t_point	my_map_pixel(t_pixel pixel, t_point min_bound,
				t_point max_bound, t_pixel pix_max);

/* build fractal */
t_fractal	*init_fractal(void);
void		add_const_to_fract(t_fractal **f);
void		draw_fractal(t_fractal *f);
int			color_pixel(t_fractal *f, t_pixel p);
void		color_all_pixels(t_fractal *f);
void		f_free(t_fractal **f, int perr_msg);
void		activate_hooks(t_fractal *f);

/* coloring schemas */
int			map_color_maxiter(int iter, int max_iter, t_point min_bound);

/* hooks */
int			close_win(int keycode, t_fractal *f);
int			close_win2(t_fractal *f);
int			my_zoom(int button, int x, int y, t_fractal *f);
int			my_move(int keycode, t_fractal *f);

#endif