/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:14:39 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 15:36:47 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, t_pixel pixel, int color)
{
	char	*dst;

	dst = data->addr + (pixel.y * data->line_length + pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void	f_free(t_fractal **f_ptr)
{
	t_fractal	*f;

	if (f_ptr == NULL || *f_ptr == NULL)
		return ;
	f = *f_ptr;
	if (f->img != NULL) 
	{
        mlx_destroy_image(f->mlx, f->img->img);
        free(f->img);
    }
    if (f->win != NULL) 
        mlx_destroy_window(f->mlx, f->win);
    free(f);
	*f_ptr = NULL;
}
