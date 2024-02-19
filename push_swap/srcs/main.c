/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 11:00:12 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

void	print_stack(t_dlist *stack)
{
	t_dlist	*tmp;
	int		content;
	int		index;

	tmp = stack;
	while (tmp)
	{
		content = tmp->content;
        index = tmp->n_cont;
		printf("content: %d, index: %d\n", content, index);
		tmp = tmp->next;
	}
}

t_dlist	*construct_input(int ac, char **av)
{
	t_dlist	*stack;
	char	**split_av;
	int		i;

	split_av = NULL;
	stack = NULL;
	//if (ac < 1 || !av)
	//	return (NULL);
	if (ac == 1)
	{
		split_av = ft_split(av[0], ' ');
        av = split_av;
        ac = 0;
        while (av[ac])
            ac ++;
	}
	if (!all_is_num(av, ac))
	{
		if (split_av)
        {
			i = 0;
            while (split_av[i])
			{
                free(split_av[i]);
				i++;
			}
            free(split_av);
        }
        return (NULL);
	}
	stack = read_input(ac, av);
	if (!stack)
    {
        if (split_av)
        {
            for (int i = 0; split_av[i]; i++)
                free(split_av[i]);
            free(split_av);
        }
        return (NULL);
    }
    calculate_indexes(&stack, ft_dlstlen(stack));
    if (split_av)
    {
        for (int i = 0; split_av[i]; i++)
            free(split_av[i]);
        free(split_av);
    }
    return (stack);
}

int	main(int ac, char **av)
{
	t_dlist	*stack_a;
	t_dlist	*stack_b;

	if (ac < 2 || (ac == 2 && *av[1] == '\0'))
		return (0);
	stack_a = construct_input(ac - 1, av + 1);
	stack_b = NULL;
	if (!stack_a)
	{
		ft_dlst_free(&stack_a);
		ft_dlst_free(&stack_b);
		return (ft_putstr_fd(ERROR, 2), 0);
	}
	//ft_printf("Original stack:\n");
	//print_stack(stack_a);
	sort_stack(&stack_a, &stack_b);
	/*printf("Stack b size: %d, Sorted stack a (expected 1):%d\n", 
				ft_dlstlen(stack_b),
				sort_check(stack_a, ASC, ft_dlstlen(stack_a)));
	print_stack(stack_a); */
	//ft_printf("Sorted stack b:\n", ft_dlstlen(stack_b));
	//print_stack(stack_b);
	ft_dlst_free(&stack_a);
	ft_dlst_free(&stack_b);
	return (0);
}
