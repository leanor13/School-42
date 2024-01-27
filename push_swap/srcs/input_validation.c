/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:26:03 by leanor            #+#    #+#             */
/*   Updated: 2024/01/27 20:56:59 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_isnum(char *s)
{
	if (!s)
		return (0);
	if (*s == '-')
		s ++;
	if (!*s)
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
