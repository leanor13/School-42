/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 21:02:45 by leanor            #+#    #+#             */
/*   Updated: 2024/01/27 21:36:53 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void test_ft_dlstnew(void)
{
    t_dlist *node = ft_dlstnew(5);
    assert(node != NULL);
    assert(node->content == 5);
    assert(node->next == NULL);
    assert(node->prev == NULL);
    free(node);
    printf("All ft_dlstnew tests passed.\n");
}

void test_ft_dlstadd_front(void)
{
    t_dlist *list = NULL;
    ft_dlstadd_front(&list, ft_dlstnew(5));
    assert(list != NULL);
    assert(list->content == 5);
    ft_dlstadd_front(&list, ft_dlstnew(10));
    assert(list->content == 10);
    assert(list->next->content == 5);
    ft_dlst_free(&list);
    printf("All ft_dlstadd_front tests passed.\n");
}

void test_ft_dlstadd_back(void)
{
    t_dlist *list = NULL;
    ft_dlstadd_back(&list, ft_dlstnew(5));
    assert(list != NULL);
    assert(list->content == 5);
    ft_dlstadd_back(&list, ft_dlstnew(10));
    assert(ft_dlstlast(list)->content == 10);
    ft_dlst_free(&list);
    printf("All ft_dlstadd_back tests passed.\n");
}

void test_ft_dlstlast(void)
{
    t_dlist *list = NULL;
    assert(ft_dlstlast(list) == NULL);
    ft_dlstadd_back(&list, ft_dlstnew(5));
    assert(ft_dlstlast(list)->content == 5);
    ft_dlstadd_back(&list, ft_dlstnew(10));
    assert(ft_dlstlast(list)->content == 10);
    ft_dlst_free(&list);
    printf("All ft_dlstlast tests passed.\n");
}

void test_ft_dlst_free(void)
{
    t_dlist *list = NULL;
    ft_dlstadd_back(&list, ft_dlstnew(5));
    ft_dlstadd_back(&list, ft_dlstnew(10));
    ft_dlst_free(&list);
    assert(list == NULL);
    printf("All ft_dlst_free tests passed.\n");
}