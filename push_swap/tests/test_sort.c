#include "tests.h"

void test_sort_3(void) 
{
    int orders[6][3] = {
        {10, 20, 30},
        {1, 33, 12},
        {12, 11, 13},
        {-2, -1, -3},
        {3, 0, 2},
        {3, 2, -1}
    };

    for (int i = 0; i < 6; i++) {
        t_dlist *stack_a = NULL;
        ft_dlstadd_back(&stack_a, ft_dlstnew(orders[i][0]));
        ft_dlstadd_back(&stack_a, ft_dlstnew(orders[i][1]));
        ft_dlstadd_back(&stack_a, ft_dlstnew(orders[i][2]));

		calculate_indexes(&stack_a, 3);
        sort_3(&stack_a);

        t_dlist *tmp = stack_a;
        assert(tmp->n_cont == 1); tmp = tmp->next;
        assert(tmp->n_cont == 2); tmp = tmp->next;
        assert(tmp->n_cont == 3); tmp = tmp->next;

        ft_dlst_free(&stack_a);
    }
	ft_putstr_fd("Sort 3 ASC tests passed.\n", 1);
}