/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:49:42 by leanor            #+#    #+#             */
/*   Updated: 2024/02/10 10:13:29 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("sa\n");
	(void)stack_b;
	ft_swap(stack_a);
}

void	ft_sb(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("sb\n");
	(void)stack_a;
	ft_swap(stack_b);
}

void	ft_ss(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_swap(stack_a);
	ft_swap(stack_b);
	ft_printf("ss\n");
}

void	ft_pa(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("pa\n");
	(void)stack_b;
	ft_push(stack_b, stack_a);
}

void	ft_pb(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("pb\n");
	ft_push(stack_a, stack_b);
}

void	ft_ra(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("ra\n");
	(void)stack_b;
	ft_rotate(stack_a);
}

void	ft_rb(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("rb\n");
	(void)stack_a;
	ft_rotate(stack_b);
}

void	ft_rr(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_rotate(stack_a);
	ft_rotate(stack_b);
	ft_printf("rr\n");
}

void	ft_rra(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("rra\n");
	(void)stack_b;
	ft_reverse_rotate(stack_a);
}

void	ft_rrb(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_printf("rrb\n");
	(void)stack_a;
	ft_reverse_rotate(stack_b);
}

void	ft_rrr(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_reverse_rotate(stack_a);
	ft_reverse_rotate(stack_b);
	ft_printf("rrr\n");
}
