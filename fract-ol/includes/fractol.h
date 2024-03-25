/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/25 13:07:40 by yioffe           ###   ########.fr       */
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
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define UP 126
#  define LEFT 123
#  define RIGHT 124
#  define DOWN 125
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_5 23
#  define KEY_I 34
#  define KEY_R 15
#  define KEY_C 8

# else
#  include "minilibx-linux/mlx.h"
#  define ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEU_D 100
#  define UP 65362
#  define LEFT 65361
#  define RIGHT 65363
#  define DOWN 65364
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_5 53
#  define KEY_I 105
#  define KEY_R 114
#  define KEY_C 99

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
	int		type;
	int		(*color_scheme)(int iter, int max_iter);
	t_point	c;
}	t_fractal;

/* fract constants */
# define MIN_BOUND	(t_point){-2, -2}
# define MAX_BOUND	(t_point){2, 2}
# define MAX_PIX	(t_pixel){500, 500}
# define MAX_ITER	500
# define DEF_COLOR	1;

/* Read input and instructions */
t_fractal	*handle_input_and_init(int ac, char **av);
void		input_instruction(void);
void		in_window_usage(void);

/* Mandelbrot fractal */
t_point		mandelbrot_iter(t_point c, t_point c_0);

/* basic img functions */
void		my_mlx_pixel_put(t_data *data, t_pixel pixel, int color);
t_point		my_map_pixel(t_pixel pixel, t_point min_bound,
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
int			map_color_maxiter(int iter, int max_iter);
int			map_color_b_w(int iter, int max_iter);
int			map_color_striped(int iter, int max_iter);

/* hooks */
int			close_win(int keycode, t_fractal *f);
int			close_win2(t_fractal *f);
int			my_zoom(int button, int x, int y, t_fractal *f);
void		my_move(int keycode, t_fractal *f);
void		my_color(int keycode, t_fractal *f);
int			key_press(int keycode, t_fractal *f);

#endif