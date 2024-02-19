/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:15:06 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 15:56:29 by yioffe           ###   ########.fr       */
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
	test_rev_rotate_operations();

	ft_putstr_fd("All tests passed.\n", 1);
	return (0);
}