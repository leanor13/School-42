/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:14:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/24 10:36:56 by yioffe           ###   ########.fr       */
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

int	map_color_maxiter2(int iter, int max_iter, t_point min_bound, t_point max_bound)
{
    double log_iter;
    int r, g, b;
    double coeff;

    // Adjust the coefficient as needed to achieve the desired color effect
    coeff = pow((max_bound.x - min_bound.x), 2) + pow((max_bound.y - min_bound.y), 2);
	//coeff = min_bound.x * min_bound.x;
	//coeff = min_bound.x;
	coeff = 1;
	
    // Calculate the normalized iteration count
    log_iter = log(iter + 1) / log(max_iter * coeff + 1);

    // Apply color transformation similar to rainbow_palette function
    r = (int)(9 * (1 - log_iter) * log_iter * log_iter * 255);
    g = (int)(15 * (1 - log_iter) * (1 - log_iter) * log_iter * 255);
    b = (int)(8.5 * (1 - log_iter) * (1 - log_iter) * (1 - log_iter) * 255);

    // Ensure color values are within the range [0, 255]
    r = clamp(r, 0, 255);
    g = clamp(g, 0, 255);
    b = clamp(b, 0, 255);

    // Combine color components into an RGB color value
    return (r << 16) | (g << 8) | b;
}

int	map_color_maxiter3(int iter, int max_iter)
{
	double	log_iter;
	int		r;
	int		g;
	int		b;
	double	coeff;

	coeff = 1;
	if (iter == max_iter) 
        coeff = -2;
	else if (iter == 0) 
	{
        r = 0;
        g = 0;
        b = 129;
        return (r << 16) | (g << 8) | b;
    }
	log_iter = log(iter + 1) / log(max_iter * coeff);
	r = (int)(255 * pow(log_iter, 2.0)) + 50;
	g = (int)(255 * pow(log_iter, 3.0));
	b = (int)(255 * fabs(sin(log_iter * M_PI)));
	//r = clamp(r, 0, 255);
    g = clamp(g, 0, 255);
    b = clamp(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
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
        coeff = -2;
	else if (iter == 0)
		coeff = 500;
	if (iter % 2 == 0)
		log_iter = log(iter + 1) / log(max_iter * coeff);
	else
		log_iter = log10(iter + 1) / log(max_iter * coeff);
	r = (int)(255 * pow(log_iter, 2.0));
	g = (int)(255 * pow(log_iter, 3.0));
	b = (int)(255 * fabs(sin(log_iter * M_PI)));
	return ((r << 16) | (g << 8) | b);
}