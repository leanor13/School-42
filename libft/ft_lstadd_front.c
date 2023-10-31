/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:40:11 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/09 18:58:22 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		if (*lst)
			new -> next = *lst;
		*lst = new;
	}
}

/* #include <stdio.h>

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (!lst || !del)
		return;

	while (*lst)
	{
		t_list *temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}

	*lst = NULL;
}

int main(void)
{
	// Create a list with an initial node
	t_list *lst = ft_lstnew("Node 1");
	if (!lst)
	{
		perror("ft_lstnew");
		return 1;
	}

	// Create new nodes to add to the front
	t_list *new1 = ft_lstnew("Node 2");
	t_list *new2 = ft_lstnew("Node 3");

	if (!new1 || !new2)
	{
		perror("ft_lstnew");
		return 1;
	}

	// Add new1 to the front of the list
	ft_lstadd_front(&lst, new1);

	// Add new2 to the front of the list
	ft_lstadd_front(&lst, new2);

	// Print the list
	t_list *current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	// Do not free the list here, as it's already freed in ft_lstclear
	ft_lstclear(&lst, free);
	return 0;
} */