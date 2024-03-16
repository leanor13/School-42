/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/16 21:52:23 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, t_point point, int color)
{
	char	*dst;

	dst = data->addr + (point.y * data->line_length + point.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_horizontal_line_put(t_data data, t_point start, int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		start.x ++;
		my_mlx_pixel_put(&data, start, color);
		i ++;
	}
}

void	my_mlx_vertical_line_put(t_data data, t_point start, int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		start.y ++;
		my_mlx_pixel_put(&data, start, color);
		i ++;
	}
}

void	my_mlx_rectangle(t_data data, t_point start, int width, int height, int color)
{
	t_point	curr_start;

	curr_start = start;
	my_mlx_horizontal_line_put(data, curr_start, width, color);
	my_mlx_vertical_line_put(data, curr_start, height, color);
	curr_start.y += height;
	my_mlx_horizontal_line_put(data, curr_start, width, color);
	curr_start.y = start.y;
	curr_start.x += width;
	my_mlx_vertical_line_put(data, curr_start, height, color);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		color;
	//t_point	point1 = {5, 5};
	//t_point	point2 = {175, 473};
	t_point	point3 = {200, 200};

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color =  0x00FF0000;
	//my_mlx_pixel_put(&img, point1, color);
	//my_mlx_horizontal_line_put(img, point2, 299, color);
	//my_mlx_vertical_line_put(img, point3, 100, color + 1000);
	my_mlx_rectangle(img, point3, 100, 200, color);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
