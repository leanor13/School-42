/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:14:39 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/27 12:15:06 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

char	*return_error_message(int perr_msg)
{
	char	*err_msg[ERROR_MSG_NUM];

	err_msg[MALLOC_FRCT] = "Error allocating memory for fractal";
	err_msg[GRAPHICS] = "Error initializing graphics";
	err_msg[WINDOW] = "Error initializing window";
	err_msg[MALLOC_IMG] = "Error allocating memory for t_data";
	err_msg[NEW_IMG] = "Error creating image";
	err_msg[IMG_ADDR] = "Error getting image address";
	if (perr_msg >= 0 && perr_msg < ERROR_MSG_NUM)
		return (err_msg[perr_msg]);
	else
		return ("Unknown error");
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
		perror(return_error_message(perr_msg));
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
