/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:14:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 21:36:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	map_color_maxiter(int iter, int max_iter, t_point min_bound)
{
	double	log_iter;
	int		r;
	int		g;
	int		b;
	double	coeff;

	coeff = pow(fabs(1 / min_bound.x), 2) + 1;
	log_iter = log(iter + 1) / log(max_iter * coeff);
	r = (int)(255 * log_iter);
	g = (int)(255 * pow(log_iter, 2));
	b = (int)(255 * fabs(sin(log_iter * M_PI)));
	return ((r << 16) | (g << 8) | b);
}
