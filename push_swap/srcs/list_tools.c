/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:54:43 by leanor            #+#    #+#             */
/*   Updated: 2024/02/13 13:10:32 by leanor           ###   ########.fr       */
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
	res->index = 0;
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
int	ft_med_count(t_dlist *lst, int len)
{
	int	*indexes;
	int	i;
	int	high;
	int	low;
	int med;

	indexes = ft_calloc(len, sizeof(int));
	if (!indexes)
		return (0);
	high = lst->index;
	low = lst->index;
	i = 0;
	while (i < len && lst)
	{
		indexes[i] = lst->index;
		if (indexes[i] > high)
			high = indexes[i];
		if (indexes[i] < low)
			low = indexes[i];
		lst = lst->next;
		i ++;
	}
	arr_qsort(indexes, low, high);
	med = indexes[len / 2];
	return (free(indexes), med);
}
