/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/18 12:54:43 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, t_pixel pixel, int color)
{
	char	*dst;

	dst = data->addr + (pixel.y * data->line_length + pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_complex	iteration_fractal(t_complex c)
{
	t_complex	next;

	next.real = c.real * c.real - c.imaginary * c.imaginary + c.real;
	next.imaginary = 2 * c.real * c.imaginary + c.imaginary;
	return (next);
}

t_complex	my_map_pixel(t_pixel pixel, t_point min_bound, t_point max_bound, t_pixel pix_max)
{
	t_complex	result;
	double		x_range;
	double		y_range;
	
	x_range = (max_bound.x - min_bound.x) / pix_max.x;
	y_range = (max_bound.y - min_bound.y) / pix_max.y;
	result.real = pixel.x * x_range + min_bound.x;
	result.imaginary = pixel.y * y_range + min_bound.y;
	return (result);
}

void	color_pixel(t_data *img, t_point min_bound, t_point max_bound, 
	t_pixel pix_max, t_pixel pixel, int iter)
{
	int			i;
	t_complex	curr;
	//t_complex	c_pixel;

	i = 0;
	curr = my_map_pixel(pixel, min_bound, max_bound, pix_max);
	while (i < iter)
	{
		curr = iteration_fractal(curr);
		if ((curr.imaginary * curr.imaginary + curr.real * curr.real > 4))
			break ;
		i ++;
	}
	if (i < iter/3)
		my_mlx_pixel_put(img, pixel, 0x00FF00);
	else if (i < (2 * iter / 3))
		my_mlx_pixel_put(img, pixel, 0xFF7F00);
	else if (i < iter)
		my_mlx_pixel_put(img, pixel, 0x0000FF);
}

void	color_all_pixels(t_data *img, t_point min_bound, t_point max_bound, 
	t_pixel pix_max, int iter)
{
	t_pixel	p;

	p = (t_pixel){0, 0};
	while (p.x < pix_max.x)
	{
		p.y = 0;
		while (p.y < pix_max.y)
		{
			color_pixel(img, min_bound, max_bound, pix_max, p, iter);
			p.y ++;
		}
		p.x ++;
	}
}

void print_mapped_complex_numbers(t_point min_bound, t_point max_bound, t_pixel pix_max) {
    t_pixel pixel;
    t_complex mapped_complex;

    for (pixel.x = 0; pixel.x < pix_max.x; pixel.x++) {
        for (pixel.y = 0; pixel.y < pix_max.y; pixel.y++) {
            mapped_complex = my_map_pixel(pixel, min_bound, max_bound, pix_max);
            printf("Pixel (%d, %d) maps to complex number (%f, %f)\n", pixel.x, pixel.y, mapped_complex.real, mapped_complex.imaginary);
        }
    }
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		color;
	int		img_height = 500;
	int		img_width = 500;
	t_pixel	pix_max = { img_height, img_width };

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, pix_max.x, pix_max.y, "Hello world!");
	img.img = mlx_new_image(mlx, pix_max.x, pix_max.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color =  0x00FF0000;
	my_mlx_horizontal_line_put(&img, (t_pixel){10, img_height / 2}, img_width - 20, color);
	my_mlx_vertical_line_put(&img, (t_pixel){img_width / 2, 10}, img_height - 20, color);
	color_all_pixels(&img, (t_point){-2.0, -2.0}, (t_point){2.0, 2.0}, pix_max, 100);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
