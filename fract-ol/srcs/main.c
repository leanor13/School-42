/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/16 15:30:15 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_horizontal_line_put(t_data data, int x_start, int y_start, int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		my_mlx_pixel_put(&data, x_start + i, y_start, color);
		i ++;
	}
}

void	my_mlx_vertical_line_put(t_data data, int x_start, int y_start, int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		my_mlx_pixel_put(&data, x_start, y_start + i, color);
		i ++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		color;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color =  0x00FF0000;
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	my_mlx_horizontal_line_put(img, 50, 50, 100, color);
	my_mlx_vertical_line_put(img, 200, 200, 100, color + 1000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
