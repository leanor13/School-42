/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:39:28 by leanor            #+#    #+#             */
/*   Updated: 2024/01/27 21:36:50 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void test_read_input(void)
{
    char *args1[] = {"program", "5", "10", "15"};
    t_dlist **list1 = read_input(4, args1);
    assert(list1 != NULL);
    assert((*list1)->content == 5);
    assert((*list1)->next->content == 10);
    assert((*list1)->next->next->content == 15);
    ft_dlst_free(list1);
    free(list1);

    char *args2[] = {"program", "5", "10", "-5"};
    t_dlist **list2 = read_input(4, args2);
    assert(list2 != NULL);

	char *args3[] = {"program", "5", "10", "5"};
	t_dlist **list3 = read_input(4, args3);
	assert(list3 == NULL);

    printf("\nAll read_input tests passed.\n");
}

void	test_ft_isnum(void)
{
	assert(ft_isnum("12345") == 1);
	assert(ft_isnum("123a5") == 0);
	assert(ft_isnum("-12345") == 1);
	assert(ft_isnum("") == 0);
	assert(ft_isnum(NULL) == 0);
	printf("\nAll ft_isnum tests passed.\n");
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
	printf("\nAll has_duplicate tests passed.\n");
}

void	test_validate_input(void)
{
	char *av[] = {"prog", "1", "2", "3", NULL};
	int ac = 4;

	assert(validate_input(av, ac) == 1);

	char *av2[] = {"prog", "1", "2", "a", NULL};
	ac = 4;

	assert(validate_input(av2, ac) == 0);
	printf("\nAll validate_input tests passed.\n");
}
