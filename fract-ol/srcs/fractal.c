/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:36:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 17:27:23 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_complex	mandelbrot_iter(t_complex c, t_complex c_0)
{
	t_complex	next;

	next.real = c.real * c.real - c.imaginary * c.imaginary + c_0.real;
	next.imaginary = 2 * c.real * c.imaginary + c_0.imaginary;
	return (next);
}

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
	(*f)->iter = MAX_ITER;
}

void	draw_fractal(t_fractal *f)
{
	color_all_pixels(f->img, f->min_bound, f->max_bound, f->pix_max, f->iter);
	mlx_put_image_to_window(f->mlx, f->win, f->img->img, 0, 0);
}

void	color_pixel(t_data *img, t_point min_bound, t_point max_bound, 
	t_pixel pix_max, t_pixel pixel, int max_iter)
{
	int			i;
	t_complex	curr;
	t_complex	c_0;
	int			color;

	i = 0;
	curr = my_map_pixel(pixel, min_bound, max_bound, pix_max);
	c_0 = curr;
	while (i < max_iter)
	{
		if ((curr.imaginary * curr.imaginary + curr.real * curr.real >= 4))
			break ;
		curr = mandelbrot_iter(curr, c_0);
		i ++;
	}
	color = map_color_maxiter(i, max_iter, min_bound);
	my_mlx_pixel_put(img, pixel, color);
}

void	color_all_pixels(t_data *img, t_point min_bound, t_point max_bound, 
	t_pixel pix_max, int max_iter)
{
	t_pixel	p;

	p = (t_pixel){0, 0};
	while (p.x < pix_max.x)
	{
		p.y = 0;
		while (p.y < pix_max.y)
		{
			color_pixel(img, min_bound, max_bound, pix_max, p, max_iter);
			p.y ++;
		}
		p.x ++;
	}
}

