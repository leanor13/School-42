/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:36:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/26 01:51:32 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_fractal	*init_fractal(void)
{
	t_fractal	*f;

	f = malloc(sizeof(t_fractal));
	if (!f)
		f_free(NULL, MALLOC_FRCT);
	f->mlx = mlx_init();
	if (!f->mlx)
		f_free(&f, GRAPHICS);
	f->win = mlx_new_window(f->mlx, MAX_PIX.x, MAX_PIX.y, "Fract-ol!");
	if (!f->win)
		f_free(&f, WINDOW);
	f->img = malloc(sizeof(t_data));
	if (!f->img)
		f_free(&f, MALLOC_IMG);
	f->img->img = mlx_new_image(f->mlx, MAX_PIX.x, MAX_PIX.y);
	if (!f->img->img)
		f_free(&f, NEW_IMG);
	f->img->addr = mlx_get_data_addr(f->img->img, &f->img->bits_per_pixel,
			&f->img->line_length, &f->img->endian);
	if (!f->img->addr)
		f_free(&f, IMG_ADDR);
	add_const_to_fract(&f);
	return (f);
}

void	add_const_to_fract(t_fractal **f)
{
	(*f)->min_bound = MIN_BOUND;
	(*f)->max_bound = MAX_BOUND;
	(*f)->pix_max = MAX_PIX;
	(*f)->iter = DEFAULT_ITER;
	(*f)->c = DEF_JULIA;
	(*f)->color_scheme = map_color_maxiter;
}

void	draw_fractal(t_fractal *f)
{
	color_all_pixels(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img->img, 0, 0);
}

void	color_all_pixels(t_fractal *f)
{
	int		*pixels;
	int		color;
	int		i;
	t_pixel	curr_pix;
	int 	(*color_func)(t_fractal *, t_pixel);

	if (f->type == MANDELBROT)
        color_func = &mandelbrot_color_pix;
    else if (f->type == JULIA)
        color_func = &julia_color_pix;
    else if (f->type == TRICORN)
        color_func = &tricorn_color_pix;
	color_func = color_pixel;
	pixels = (int *)f->img->addr;
	i = 0;
	while (i < f->pix_max.x * f->pix_max.y)
	{
		curr_pix.x = i % f->pix_max.x;
		curr_pix.y = i / f->pix_max.x;
		color = color_func(f, curr_pix);
		pixels[i] = color;
		i ++;
	}
}
