#ifndef TESTS_H
# define TESTS_H

# include <assert.h>
# include "../includes/push_swap.h"
# include <stdio.h>

void	test_ft_isnum(void);
void	test_has_duplicate(void);
void	test_validate_input(void);
void	test_read_input(void);
void	test_calculate_indexes(void);

void	test_ft_dlstnew(void);
void	test_ft_dlstadd_front(void);
void	test_ft_dlstadd_back(void);
void	test_ft_dlstlast(void);
void	test_ft_dlst_free(void);

void	test_ft_detach_node(void);
void	test_ft_swap(void);
void	test_ft_push(void);
void	test_ft_rotate(void);
void	test_ft_reverse_rotate(void);

void	test_swap_operations(void);
void	test_rev_rotate_operations(void);
void	test_sort_3(void);

#endif
