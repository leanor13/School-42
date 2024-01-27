/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:39:28 by leanor            #+#    #+#             */
/*   Updated: 2024/01/27 20:39:19 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "tests.h"

void	test_ft_isnum(void)
{
	assert(ft_isnum("12345") == 1);
	assert(ft_isnum("123a5") == 0);
	assert(ft_isnum("-12345") == 1);
	assert(ft_isnum("") == 0);
	assert(ft_isnum(NULL) == 0);
	printf("All ft_isnum tests passed.\n");
}

void	test_has_duplicate(void)
{
	t_dlist	*stack = NULL;

	// Add some elements to the stack
	ft_dlstadd_back(&stack, ft_dlstnew(1));
	ft_dlstadd_back(&stack, ft_dlstnew(2));
	ft_dlstadd_back(&stack, ft_dlstnew(3));

	assert(has_duplicate(&stack) == 0);

	// Add a duplicate element to the stack
	ft_dlstadd_back(&stack, ft_dlstnew(1));

	assert(has_duplicate(&stack) == 1);
	printf("All has_duplicate tests passed.\n");
}

void	test_validate_input(void)
{
	char *av[] = {"prog", "1", "2", "3", NULL};
	int ac = 4;

	assert(validate_input(av, ac) == 1);

	char *av2[] = {"prog", "1", "2", "a", NULL};
	ac = 4;

	assert(validate_input(av2, ac) == 0);
	printf("All validate_input tests passed.\n");
}
