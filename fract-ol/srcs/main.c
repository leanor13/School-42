/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/16 22:46:58 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, t_point point, int color)
{
	char	*dst;

	dst = data->addr + (point.y * data->line_length + point.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_horizontal_line_put(t_data *data, t_point start, int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		start.x ++;
		my_mlx_pixel_put(data, start, color);
		i ++;
	}
}

void	my_mlx_vertical_line_put(t_data *data, t_point start, int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		start.y ++;
		my_mlx_pixel_put(data, start, color);
		i ++;
	}
}

void	my_mlx_rectangle(t_data *data, t_point start, int width, int height, int color)
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

void	my_mlx_filled_rectangle(t_data *data, t_point start, int width, int height, int color)
{
	int	i = 0;
	int strip_height = height/NUM_RAINBOW_COLORS;
	int	color_index = 0;
	int strip_count = 0;
	int	curr_color;

	(void)color;
	while (i < height)
	{
		curr_color = rainbow_colors[color_index];
		my_mlx_horizontal_line_put(data, (t_point){start.x, start.y + i}, width, curr_color);
		strip_count ++;
		if (strip_count >= strip_height)
		{
			strip_count = 0;
			color_index ++;
		}
		i ++;
	}
}

void my_mlx_circle(t_data *data, t_point center, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        my_mlx_pixel_put(data, (t_point){center.x + x, center.y + y}, color);
        my_mlx_pixel_put(data, (t_point){center.x + y, center.y + x}, color);
        my_mlx_pixel_put(data, (t_point){center.x - y, center.y + x}, color);
        my_mlx_pixel_put(data, (t_point){center.x - x, center.y + y}, color);
        my_mlx_pixel_put(data, (t_point){center.x - x, center.y - y}, color);
        my_mlx_pixel_put(data, (t_point){center.x - y, center.y - x}, color);
        my_mlx_pixel_put(data, (t_point){center.x + y, center.y - x}, color);
        my_mlx_pixel_put(data, (t_point){center.x + x, center.y - y}, color);
		color += 5000;
        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void draw_circle_filled(t_data *data, t_point center, int radius, int color)
{
    int x, y;

    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put(data, (t_point){center.x + x, center.y + y}, color);
				color += 1000;
            }
			color += 1000;
        }
		color += 1000;
    }
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
	my_mlx_filled_rectangle(&img, point3, 100, 200, color);
	//my_mlx_circle(&img, point3, 100, color);
	//draw_circle_filled(&img, point3, 100, color);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
