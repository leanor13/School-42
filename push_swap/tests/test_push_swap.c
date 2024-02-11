/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:15:06 by leanor            #+#    #+#             */
/*   Updated: 2024/02/11 12:01:52 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	test_read_input();
	test_ft_isnum();
	test_has_duplicate();
	test_validate_input();
	test_ft_dlstnew();
    test_ft_dlstadd_front();
    test_ft_dlstadd_back();
    test_ft_dlstlast();
    test_ft_dlst_free();
	test_ft_detach_node();
	test_ft_swap();
	test_ft_push();
	test_ft_rotate();
	test_ft_reverse_rotate();
	test_swap_operations();
	test_calculate_indexes();
	test_sort_3();

	ft_printf("All tests passed.\n");
	return (0);
}