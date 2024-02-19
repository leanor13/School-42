/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:26:03 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 11:46:15 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_dlist	*create_node(t_dlist *stack, char *av)
{
	int		num;
	t_dlist	*new_node;

	num = ft_atoi_custom(av);
	if (num == 0 && av[0] != '0')
	{
		ft_dlst_free(&stack);
		return (NULL);
	}
	new_node = ft_dlstnew(num);
	if (!new_node)
	{
		ft_dlst_free(&stack);
		return (NULL);
	}
	return (new_node);
}

t_dlist	*read_input(int ac, char **av)
{
	t_dlist	*stack;
	t_dlist	*new_node;
	int		i;

	stack = NULL;
	i = 0;
	while (i < ac)
	{
		new_node = create_node(stack, av[i]);
		if (!new_node)
			return (NULL);
		ft_dlstadd_back(&stack, new_node);
		i++;
	}
	if (has_duplicate(stack))
	{
		ft_dlst_free(&stack);
		return (NULL);
	}
	return (stack);
}

int	ft_isnum(char *s)
{
	if (!s)
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (0);
	if (*s == '0' && *(s + 1) != '\0')
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	has_duplicate(t_dlist *stack)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	tmp = stack;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp->content == tmp2->content)
				return (1);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	all_is_num(char **av, int ac)
{
	while (ac >= 1)
	{
		if (!ft_isnum(av[ac - 1]))
			return (0);
		ac--;
	}
	return (1);
}

void	calculate_indexes(t_dlist **stack, int len)
{
	int		i;
	t_dlist	*tmp;
	t_dlist	*inner;
	int		count;

	tmp = *stack;
	count = 0;
	while (tmp && count < len)
	{
		i = 1;
		inner = *stack;
		while (inner)
		{
			if (inner->content < tmp->content)
				i++;
			inner = inner->next;
		}
		tmp->n_cont = i;
		tmp = tmp->next;
		count++;
	}
}
