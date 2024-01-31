/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_swap_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:49:08 by leanor            #+#    #+#             */
/*   Updated: 2024/01/31 13:53:22 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

/* static void	print_stack(t_dlist *stack)
{
	t_dlist	*tmp;

	tmp = stack;
	while (tmp)
	{
		ft_printf("%d\n", tmp->content);
		tmp = tmp->next;
	}
} */

void	test_swap_operations(void)
{
	t_dlist	*stack_a;
	t_dlist	*stack_b;
	t_dlist	*current;
	int		values_a[] = {2, 1, 3, 6, 5, 8};
	int		expected_values_a[] = {1, 2, 3, 5, 6, 8};
	int		i;

	stack_a = NULL;
	stack_b = NULL;
	for (i = 0; i < 6; i++)
        ft_dlstadd_back(&stack_a, ft_dlstnew(values_a[i]));

	ft_sa(&stack_a, &stack_b);
	ft_pb(&stack_a, &stack_b);
	ft_pb(&stack_a, &stack_b);
	ft_pb(&stack_a, &stack_b);
	ft_ra(&stack_a, &stack_b);
	ft_rb(&stack_a, &stack_b);
	ft_rrr(&stack_a, &stack_b);
	ft_sa(&stack_a, &stack_b);
	ft_pa(&stack_a, &stack_b);
	ft_pa(&stack_a, &stack_b);
	ft_pa(&stack_a, &stack_b);
	
	assert(stack_b == NULL);

	current = stack_a;
    for (i = 0; i < 6; i++)
    {
        assert(current != NULL);
        assert(current->content == expected_values_a[i]);
        current = current->next;
    }
    assert(current == NULL);
	
	ft_dlst_free(&stack_a);
	ft_dlst_free(&stack_b);
	printf("Swap operations test OK\n");
}