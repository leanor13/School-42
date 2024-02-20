/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:52:41 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/20 17:32:42 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	error_return(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_dlst_free(stack_a);
	ft_dlst_free(stack_b);
	ft_putstr_fd(ERROR, 2);
	return (0);
}

int	p_s(const char *command, t_dlist **stack_a, t_dlist **stack_b) 
{
	if (!ft_strcmp(command, "sa\n"))
		ft_s(stack_a, A, SILENT);
	else if (!ft_strcmp(command, "sb\n"))
		ft_s(stack_b, B, SILENT);
	else if (!ft_strcmp(command, "pa\n"))
		ft_p(stack_a, stack_b, A, SILENT);
	else if (!ft_strcmp(command, "pb\n"))
		ft_p(stack_a, stack_b, B, SILENT);
	else if (!ft_strcmp(command, "ra\n"))
		ft_r(stack_a, A, SILENT);
	else if (!ft_strcmp(command, "rb\n"))
		ft_r(stack_b, B, SILENT);
	else if (!ft_strcmp(command, "rra\n"))
		ft_rr(stack_a, A, SILENT);
	else if (!ft_strcmp(command, "rrb\n"))
		ft_rr(stack_b, B, SILENT);
	else if (!ft_strcmp(command, "ss\n"))
		ft_ss(stack_a, stack_b, SILENT);
	else if (!ft_strcmp(command, "rr\n"))
		ft_rr_both(stack_a, stack_b, SILENT);
	else if (!ft_strcmp(command, "rrr\n"))
		ft_rrr(stack_a, stack_b, SILENT);
	else
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
    t_dlist *stack_a = NULL;
    t_dlist *stack_b = NULL;
    char *action;

    if (ac >= 2 && av[1][0] != '\0') 
	{
        stack_a = construct_input(ac - 1, av + 1);
        if (!stack_a)
            return (error_return(&stack_a, &stack_b));
    }

    while ((action = get_next_line(0)) != NULL && *action != '\0') 
	{
        if (!p_s(action, &stack_a, &stack_b)) 
		{
            free(action);
            return (error_return(&stack_a, &stack_b));
        }
        free(action);
    }

    if (sort_check(stack_a) && ft_dlstlen(stack_b) == 0)
        ft_putstr_fd("OK\n", 1);
    else
        ft_putstr_fd("KO\n", 1);

    ft_dlst_free(&stack_a);
    ft_dlst_free(&stack_b);

    return 0;
}
