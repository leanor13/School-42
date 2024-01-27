/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_swap_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 21:35:54 by leanor            #+#    #+#             */
/*   Updated: 2024/01/27 21:41:58 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void test_ft_detach_node(void)
{
    t_dlist *node1 = ft_dlstnew(1);
    t_dlist *node2 = ft_dlstnew(2);
    ft_dlstadd_back(&node1, node2);
    t_dlist *detached = ft_detach_node(&node1, node2);
    assert(node1->next == NULL);
    assert(detached->prev == NULL);
    assert(detached->next == NULL);
    assert(detached->content == 2);
}

void test_ft_swap(void)
{
    t_dlist *node1 = ft_dlstnew(1);
    t_dlist *node2 = ft_dlstnew(2);
    ft_dlstadd_back(&node1, node2);
    ft_swap(&node1);
    assert(node1->content == 2);
    assert(node1->next->content == 1);
}

void test_ft_push(void)
{
    t_dlist *stack_from = ft_dlstnew(1);
    t_dlist *stack_to = ft_dlstnew(2);
    ft_push(&stack_from, &stack_to);
    assert(stack_from == NULL);
    assert(stack_to->content == 1);
    assert(stack_to->next->content == 2);
}

void test_ft_rotate(void)
{
    t_dlist *node1 = ft_dlstnew(1);
    t_dlist *node2 = ft_dlstnew(2);
    ft_dlstadd_back(&node1, node2);
    ft_rotate(&node1);
    assert(node1->content == 2);
    assert(node1->next->content == 1);
}

void test_ft_reverse_rotate(void)
{
    t_dlist *node1 = ft_dlstnew(1);
    t_dlist *node2 = ft_dlstnew(2);
    ft_dlstadd_back(&node1, node2);
    ft_reverse_rotate(&node1);
    assert(node1->content == 2);
    assert(node1->next->content == 1);
}