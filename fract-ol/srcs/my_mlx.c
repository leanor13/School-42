/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:14:39 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/27 11:35:06 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_point	my_map_pixel(t_pixel pixel, t_point min_bound, t_point max_bound,
		t_pixel pix_max)
{
	t_point	result;
	double	x_range;
	double	y_range;

	x_range = (max_bound.x - min_bound.x) / pix_max.x;
	y_range = (max_bound.y - min_bound.y) / pix_max.y;
	result.x = pixel.x * x_range + min_bound.x;
	result.y = pixel.y * y_range + min_bound.y;
	return (result);
}

static void	exit_with_status(int perr_msg)
{
	if (perr_msg > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	f_free(t_fractal **f_ptr, int perr_msg)
{
	t_fractal	*f;

	if (perr_msg >= 0)
		perror(err_msg[perr_msg]);
	if (f_ptr == NULL || *f_ptr == NULL)
		exit_with_status(perr_msg);
	f = *f_ptr;
	if (f->img != NULL)
	{
		mlx_destroy_image(f->mlx, f->img->img);
		free(f->img);
	}
	if (f->win != NULL)
		mlx_destroy_window(f->mlx, f->win);
	if (!IS_APPLE)
		mlx_destroy_display(f->mlx);
	free(f->mlx);
	free(f);
	*f_ptr = NULL;
	exit_with_status(perr_msg);
}
