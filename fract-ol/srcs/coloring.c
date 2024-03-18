/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_schemas.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:14:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/18 22:15:04 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int map_color_general(int iter) 
{
    // Calculate color channels based on iteration count
    int r = (iter * 8) % 256;  // Red channel
    int g = (iter * 4) % 256;  // Green channel
    int b = (iter * 16) % 256; // Blue channel
    return (r << 16) + (g << 8) + b;  // Combine RGB components
}

int map_color_maxiter(int iter, int max_iter) 
{
    double logIter = log(iter + 1) / log(max_iter + 1);

    int r = (int)(255 * logIter);  // Red component
    int g = (int)(255 * pow(logIter, 2));  // Green component
    int b = (int)(255 * fabs(tan(logIter * M_PI)));  // Blue component
    int color = (r << 16) | (g << 8) | b;

    return color;
}

int map_color_maxiter2(int iter, int max_iter) 
{
    // Calculate color channels based on iteration count
    double logIter = log(iter + 1) / log(max_iter + 1);

    // Apply non-linear transformation to exaggerate contrast near edges
    double transformedIter = pow(logIter, 2); // Cubic transformation

    // Map the transformed iteration count to a color gradient
    int r = (int)(255 * transformedIter);  // Red component
    int g = (int)(255 * (1 - transformedIter));  // Green component
    int b = (int)(255 * fabs(sin(transformedIter * M_PI)));  // Blue component

    // Combine the color components
    int color = (r << 16) | (g << 8) | b;

    return color;
}