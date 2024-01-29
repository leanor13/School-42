/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:48:35 by leanor            #+#    #+#             */
/*   Updated: 2024/01/29 11:53:23 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_dlist	*ft_detach_node(t_dlist **stack, t_dlist *node)
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
	(*stack)->next = tmp;
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
	t_dlist	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	*stack = ft_dlstlast(*stack);
	(*stack)->next = tmp;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}
