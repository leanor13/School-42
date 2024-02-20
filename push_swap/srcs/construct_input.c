/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:14:58 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/20 21:21:09 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_dlist	*construct_input(int ac, char **av)
{
	t_dlist	*stack;
	char	**split_av;

	split_av = NULL;
	stack = NULL;
	if (ac == 1)
	{
		split_av = ft_split(av[0], ' ');
		av = split_av;
		ac = 0;
		while (av[ac])
			ac++;
	}
	if (!all_is_num(av, ac))
		return (free_split(split_av), NULL);
	stack = read_input(ac, av);
	if (!stack)
		return (free_split(split_av), NULL);
	free_split(split_av);
	return (stack);
}

int	sort_check(t_dlist *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->content > stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	sort_stack(t_dlist **stack_a, t_dlist **stack_b)
{
	int	size;

	if (!stack_a || !*stack_a || sort_check(*stack_a))
		return ;
	size = ft_dlstlen(*stack_a);
	if (size == 2)
		sort_2(stack_a);
	else if (size == 3)
		sort_3(stack_a);
	else
		big_sort(stack_a, stack_b);
}
