/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:38:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 16:39:07 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

#define NUM_ERRORS 8

enum ErrorCodes
{
    NO_ERROR = -1,
	NOT_PRINTABLE = 0,
	MALLOC_FRCT = 1,
    GRAPHICS = 2,
    WINDOW = 3,
	MALLOC_IMG = 4,
	NEW_IMG = 5,
	IMG_ADDR = 6
};

static const char *ERR_MSG[NUM_ERRORS] = 
{
    "No error",
    "Not printable error",
    "Error allocating memory for fractal",
    "Error initializing graphics",
    "Error initializing window",
    "Error allocating memory for t_data",
    "Error creating image",
    "Error getting image address",
};

#endif