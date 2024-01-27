/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:15:06 by leanor            #+#    #+#             */
/*   Updated: 2024/01/27 20:39:41 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "tests.h"

int	main(void)
{
	test_ft_isnum();
	test_has_duplicate();
	test_validate_input();
	ft_printf("All tests passed.\n");
	return (0);
}