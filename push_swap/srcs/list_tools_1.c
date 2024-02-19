/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:54:43 by leanor            #+#    #+#             */
/*   Updated: 2024/02/19 17:05:26 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_dlist	*ft_dlstnew(int content)
{
	t_dlist	*res;

	res = ft_calloc(1, sizeof(t_dlist));
	if (!res)
		return (NULL);
	res->content = content;
	res->n_cont = 0;
	res->next = NULL;
	res->prev = NULL;
	res->target = NULL;
	res->curr_pos = 0;
	res->direct_rotate = true;
	res->move_price = 0;
	return (res);
}

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

void	ft_dlst_free(t_dlist **lst)
{
	t_dlist	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	t_dlist	*curr;

	curr = lst;
	if (curr == NULL)
		return (NULL);
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}
