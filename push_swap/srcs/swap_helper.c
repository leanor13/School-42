/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:48:35 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 17:01:00 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_dlist	*ft_detach_node(t_dlist **stack, t_dlist *node)
{
	if (!*stack || !node)
		return (NULL);
	if (*stack == node)
		*stack = node->next;
	else
	{
		node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_swap(t_dlist **stack)
{
	t_dlist	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = (*stack)->next;
	if (tmp->next)
		tmp->next->prev = tmp;
	(*stack)->next = tmp;
	tmp->prev = *stack;
}

void	ft_push(t_dlist **stack_from, t_dlist **stack_to)
{
	t_dlist	*tmp;

	if (!stack_from || !*stack_from || !stack_to)
		return ;
	tmp = ft_detach_node(stack_from, *stack_from);
	tmp->next = NULL;
	tmp->prev = NULL;
	ft_dlstadd_front(stack_to, tmp);
}

void	ft_rotate(t_dlist **stack)
{
	t_dlist	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = ft_detach_node(stack, *stack);
	ft_dlstadd_back(stack, tmp);
}

void	ft_reverse_rotate(t_dlist **stack)
{
	t_dlist	*last;
	t_dlist	*second_last;

	if (!*stack || !(*stack)->next)
		return ;
	last = ft_dlstlast(*stack);
	second_last = last->prev;
	second_last->next = NULL;
	last->prev = NULL;
	last->next = *stack;
	(*stack)->prev = last;
	*stack = last;
}
