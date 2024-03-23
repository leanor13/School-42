/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:14:39 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/23 22:00:10 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, t_pixel pixel, int color)
{
	char	*dst;

	dst = data->addr
		+ (pixel.y * data->line_length
			+ pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

t_point	my_map_pixel(t_pixel pixel, t_point min_bound,
		t_point max_bound, t_pixel pix_max)
{
	t_point	result;
	double		x_range;
	double		y_range;

	x_range = (max_bound.x - min_bound.x) / pix_max.x;
	y_range = (max_bound.y - min_bound.y) / pix_max.y;
	result.x = pixel.x * x_range + min_bound.x;
	result.y = pixel.y * y_range + min_bound.y;
	return (result);
}

void	f_free(t_fractal **f_ptr, int perr_msg)
{
	t_fractal	*f;

	if (perr_msg > 0)
		perror(err_msg[perr_msg]);
	if (f_ptr == NULL || *f_ptr == NULL)
	{
		if (perr_msg >= 0)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	f = *f_ptr;
	if (f->img != NULL)
	{
		mlx_destroy_image(f->mlx, f->img->img);
		free(f->img);
	}
	if (f->win != NULL)
		mlx_destroy_window(f->mlx, f->win);
	#ifdef __unix__
		mlx_destroy_display(f->mlx);
	#endif
	free(f->mlx);
	free(f);
	*f_ptr = NULL;
	if (perr_msg >= 0)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}
