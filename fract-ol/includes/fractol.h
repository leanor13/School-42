/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/27 20:37:15 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

# ifdef __APPLE__
#  include "minilibx-mac/mlx.h"
#  define IS_APPLE 1
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
#  include <X11/keysym.h>
#  define IS_APPLE 0
#  define ESC XK_Escape
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

# define ERROR_MSG_NUM 6

enum e_error_codes
{
	NO_ERROR = -1,
	MALLOC_FRCT = 0,
	GRAPHICS = 1,
	WINDOW = 2,
	MALLOC_IMG = 3,
	NEW_IMG = 4,
	IMG_ADDR = 5
};

/* movement constants*/
# define ZOOM_IN 1.1
# define ZOOM_OUT 0.9
# define DBL_MIN 2.2250738585072014e-308
# define DBL_MAX 1.7976931348623157e+308

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

typedef struct fractal	t_fractal;

typedef struct fractal
{
	t_data	*img;
	void	*mlx;
	void	*win;
	t_pixel	pix_max;
	t_point	min_bound;
	t_point	max_bound;
	int		iter;
	int		(*color_pix_fun)(t_fractal *f, t_pixel pixel);
	int		(*color_scheme)(int iter, int max_iter);
	t_point	c;
}	t_fractal;

/* fract constants */
# define MIN_BOUND -2.0
# define MAX_BOUND 2.0
# define MAX_PIX 500
# define DEFAULT_ITER 100
# define MIN_ITER 2
# define MAX_ITER 999
# define DEF_COLOR 1
# define DEF_JULIA_X -0.79
# define DEF_JULIA_Y 0.15
# define MIN_JULIA -2.0
# define MAX_JULIA 2.0
# define NEG_ERROR -1

/* Read input and instructions */
t_fractal	*handle_input_and_init(int ac, char **av);
void		input_instruction(void);
void		in_window_usage(void);

/* basic img functions */
t_point		my_map_pixel(t_pixel pixel, t_point min_bound,
				t_point max_bound, t_pixel pix_max);

/* build fractal */
t_fractal	*init_fractal(void);
void		add_const_to_fract(t_fractal **f);
void		draw_fractal(t_fractal *f);
void		color_all_pixels(t_fractal *f);
void		f_free(t_fractal **f, int perr_msg);
void		activate_hooks(t_fractal *f);

/* hooks */
int			close_win(t_fractal *f);
int			my_zoom(int button, int x, int y, t_fractal *f);
void		my_move(int keycode, t_fractal *f);
int			key_press(int keycode, t_fractal *f);
int			key_hold(int keycode, t_fractal *f);

/* coloring schemas */
int			map_color_maxiter(int iter, int max_iter);
int			map_color_b_w(int iter, int max_iter);
int			map_color_striped(int iter, int max_iter);

/* Fractal coloring functions */
int			mandelbrot_color_pix(t_fractal *f, t_pixel pixel);
int			julia_color_pix(t_fractal *f, t_pixel pixel);
int			tricorn_color_pix(t_fractal *f, t_pixel pixel);

# ifdef __APPLE__

void		mlx_destroy_display(void *mlx_ptr);
# endif

#endif