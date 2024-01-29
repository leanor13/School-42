/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:54:43 by leanor            #+#    #+#             */
/*   Updated: 2024/01/29 12:14:40 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

t_dlist	*ft_dlstnew(int content)
{
	t_dlist	*res;

	res = (t_dlist *)malloc(sizeof(t_dlist));
	if (!res)
		return (ft_printf(ERROR), NULL);
	res->content = content;
	res->next = NULL;
	res->prev = NULL;
	return (res);
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

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new_node)
{
	t_dlist	*last;

	if (lst == NULL || new_node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
	}
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
}

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new_node)
{
	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
	}
	else
	{
		new_node->next = *lst;
		(*lst)->prev = new_node;
		*lst = new_node;
	}
}
