/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:14:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/27 11:19:03 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int clamp(int value, int min, int max) 
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else 
		return value;
}

int	map_color_maxiter(int iter, int max_iter)
{
	double	log_iter;
	int		r;
	int		g;
	int		b;
	double	coeff;

	coeff = 1;
	if (iter == max_iter) 
	{
		r = 0;
		g = 0;
		b = 0;
		return (r << 16) | (g << 8) | b;
	}
	else if (iter == 0)
		coeff = 500;
	log_iter = log(iter + 1) / log(max_iter * coeff);
	r = (int)(255 * pow(log_iter, 2.0));
	g = (int)(255 * pow(log_iter, 3.0));
	b = (int)(255 * fabs(sin(log_iter * M_PI)));
	return ((r << 16) | (g << 8) | b);
}

int	map_color_striped(int iter, int max_iter)
{
	double	log_iter;
	int		r;
	int		g;
	int		b;
	double	coeff;

	coeff = 1;
	if (iter == max_iter) 
	{
		r = 0;
		g = 0;
		b = 0;
		return (r << 16) | (g << 8) | b;
	}
	if (iter % 2 == 0)
		log_iter = log(iter + 1) / log(max_iter * coeff);
	else
		log_iter = log10(iter + 1) / log(max_iter * coeff);
	r = (int)(255 * pow(log_iter, 2.0));
	g = (int)(255 * pow(log_iter, 3.0));
	b = (int)(255 * fabs(sin(log_iter * M_PI)));
	return ((r << 16) | (g << 8) | b);
}

int	map_color_b_w(int iter, int max_iter)
{
	int		r;
	int		g;
	int		b;

	if (iter == max_iter) 
	{
		r = 0;
		g = 0;
		b = 0;
		return (r << 16) | (g << 8) | b;
	}
	else
	{
		r = 255;
		g = 255;
		b = 255;
		return (r << 16) | (g << 8) | b;
	}
	return ((r << 16) | (g << 8) | b);
}