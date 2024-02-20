/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:26:03 by leanor            #+#    #+#             */
/*   Updated: 2024/02/20 13:09:17 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

int	ft_atoi_custom(const char *str)
{
	int		sign;
	long	number;

	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	sign = 1;
	if (*str == 45 || *str == 43)
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	number = 0;
	while (ft_isdigit(*str))
	{
		number = 10 * number + (*str - '0');
		if ((number > INT_MAX && sign == 1) || (number > (long)INT_MAX + 1
				&& sign == -1))
			return (0);
		str++;
	}
	return (sign * number);
}
