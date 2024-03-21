
#include "../includes/fractol.h"

void print_mapped_complex_numbers(t_point min_bound, t_point max_bound, t_pixel pix_max) 
{
	t_pixel pixel;
	t_complex mapped_complex;

	for (pixel.x = 0; pixel.x < pix_max.x; pixel.x++) {
		for (pixel.y = 0; pixel.y < pix_max.y; pixel.y++) 
		{
			mapped_complex = my_map_pixel(pixel, min_bound, max_bound, pix_max);
			printf("Pixel (%d, %d) maps to complex number (%f, %f)\n", pixel.x, pixel.y, mapped_complex.real, mapped_complex.imaginary);
		}
	}
}

t_pixel map_coordinate_to_pixel(t_complex coord, t_point min_bound, t_point max_bound, t_pixel pix_max) 
{
	double x_range = (max_bound.x - min_bound.x) / pix_max.x;
	double y_range = (max_bound.y - min_bound.y) / pix_max.y;
	int x = (coord.real - min_bound.x) / x_range;
	int y = (coord.imaginary - min_bound.y) / y_range;
	return (t_pixel){x, y};
}

void	my_mlx_horizontal_line_put(t_data *data, t_pixel start, int len, int color)
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

void	my_mlx_vertical_line_put(t_data *data, t_pixel start, int len, int color)
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

void	my_mlx_rectangle(t_data *data, t_pixel start, int width, int height, int color)
{
	t_pixel	curr_start;

	curr_start = start;
	my_mlx_horizontal_line_put(data, curr_start, width, color);
	my_mlx_vertical_line_put(data, curr_start, height, color);
	curr_start.y += height;
	my_mlx_horizontal_line_put(data, curr_start, width, color);
	curr_start.y = start.y;
	curr_start.x += width;
	my_mlx_vertical_line_put(data, curr_start, height, color);
}

void	my_mlx_filled_rectangle(t_data *data, t_pixel start, int width, int height, int color)
{
	int	i = 0;
	int strip_height = height/NUM_RAINBOW_COLORS;
	int	color_index = 0;
	int strip_count = 0;
	int	curr_color;

	(void)color;
	while (i < height)
	{
		curr_color = my_rainbow_colors[color_index];
		my_mlx_horizontal_line_put(data, (t_pixel){start.x, start.y + i}, width, curr_color);
		strip_count ++;
		if (strip_count >= strip_height)
		{
			strip_count = 0;
			color_index ++;
		}
		i ++;
	}
}

void my_mlx_circle(t_data *data, t_pixel center, int radius, int color)
{
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		my_mlx_pixel_put(data, (t_pixel){center.x + x, center.y + y}, color);
		my_mlx_pixel_put(data, (t_pixel){center.x + y, center.y + x}, color);
		my_mlx_pixel_put(data, (t_pixel){center.x - y, center.y + x}, color);
		my_mlx_pixel_put(data, (t_pixel){center.x - x, center.y + y}, color);
		my_mlx_pixel_put(data, (t_pixel){center.x - x, center.y - y}, color);
		my_mlx_pixel_put(data, (t_pixel){center.x - y, center.y - x}, color);
		my_mlx_pixel_put(data, (t_pixel){center.x + y, center.y - x}, color);
		my_mlx_pixel_put(data, (t_pixel){center.x + x, center.y - y}, color);
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

void draw_circle_filled(t_data *data, t_pixel center, int radius, int color)
{
	int x, y;

	for (y = -radius; y <= radius; y++)
	{
		for (x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				my_mlx_pixel_put(data, (t_pixel){center.x + x, center.y + y}, color);
				color += 1000;
			}
			color += 1000;
		}
		color += 1000;
	}
}
