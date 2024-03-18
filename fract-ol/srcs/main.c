/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/18 22:28:21 by yioffe           ###   ########.fr       */
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

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		img_height = 500;
	int		img_width = 500;
	t_pixel	pix_max = { img_height, img_width };
	t_point	min_bound = {-2.0, -2.0};
	t_point	max_bound = {2.0, 2.0};
	int		max_iter = 100;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, pix_max.x, pix_max.y, "Hello world!");
	img.img = mlx_new_image(mlx, pix_max.x, pix_max.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color_all_pixels(&img, min_bound, max_bound, pix_max, max_iter);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
