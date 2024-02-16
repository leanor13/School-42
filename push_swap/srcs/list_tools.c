/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:54:43 by leanor            #+#    #+#             */
/*   Updated: 2024/02/16 13:02:15 by leanor           ###   ########.fr       */
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

	res = ft_calloc(1, sizeof(t_dlist));
	if (!res)
		return (NULL);
	res->content = content;
	res->n_cont = 0;
	res->next = NULL;
	res->prev = NULL;
	res->stack_position = 0;
	res->above_med = false;
	res->candidate = false;
	res->move_price = 0;
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
		last = ft_dlstlast(*lst);
		last->next = new_node;
		new_node->prev = last;
	}
}
/*
TODO: remove if not needed
*/
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
int	ft_dlstlen(t_dlist *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len ++;
		lst = lst->next;
	}
	return (len);
}

