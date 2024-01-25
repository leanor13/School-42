/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/25 15:53:37 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_isnum(char *s)
{
	if (*s == '-')
		s ++;
	if (!s || !*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
		{
			ft_printf(ERROR_INVALID_CHARACTERS);
			return (0);
		}
		else
			s ++;
	}
	return (1);
}

int	has_duplicate(t_dlist **stack)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	tmp = *stack;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp->content == tmp2->content)
			{
				ft_printf(ERROR_DUPLICATE);
				return (1);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	validate_input(char **av, int ac)
{
	while (ac >= 2)
	{
		if (!ft_isnum(av[ac - 1]))			
			return (0);
		ac --;
	}
	return (1);
}

t_dlist	**read_input(int ac, char **av)
{
	t_dlist	**stack;
	t_dlist	*new_node;
	int		num;
	int		i;

	stack = ft_calloc(ac, sizeof(t_dlist *));
	if (!stack)
		return (ft_printf(ERROR_MALLOC), NULL);
	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		new_node = ft_dlstnew(num);
		if (!new_node)
		{
			ft_dlst_free(stack);
			return (ft_printf(ERROR_MALLOC), NULL);
		}
		ft_dlstadd_back(stack, new_node);
		i ++;
	}
	if (has_duplicate(stack))
		ft_dlst_free(stack);
	return (stack);
}

void	print_stack(t_dlist **stack)
{
	t_dlist	*tmp;

	tmp = *stack;
	while (tmp)
	{
		ft_printf("%d\n", tmp->content);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_dlist	**stack_a;
	t_dlist	**stack_b;

	stack_a = NULL;
	if (ac < 2)
	{
		ft_printf(ERROR_EMPTY_INPUT);
		return (0);
	}
	if (validate_input(av, ac))
	{
		stack_a = read_input(ac, av);
		if (!stack_a)
			return (0);
		stack_b = ft_calloc(ac, sizeof(t_dlist *));
		if (!stack_b)
			return (ft_printf(ERROR_MALLOC), 0);
		print_stack(stack_a);
		ft_dlst_free(stack_a);
		ft_dlst_free(stack_b);
	}
	return (0);
}
