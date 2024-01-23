/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:21:23 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/23 11:41:20 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*last;

	if (!new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	else
	{
		last = ft_lstlast(*lst);
		last -> next = new_node;
	}
}

/*#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (!lst || !del)
		return;

	t_list *current = *lst;
	while (current)
	{
		t_list *next = current->next;
		del(current->content);
		free(current);
		current = next;
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
	t_list *new3 = ft_lstnew("Node 4");

	if (!new1 || !new2)
	{
		perror("ft_lstnew");
		return 1;
	}

	// Add new1 to the front of the list
	ft_lstadd_front(&lst, new1);

	// Add new2 to the front of the list
	ft_lstadd_front(&lst, new2);

	// Add new3 to the end of the list
	ft_lstadd_back(&lst, new3);

	// Print the list
	t_list *current = lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}

	// Print last item
	printf("last value: %s\n", (char *)ft_lstlast(lst)->content);

	return 0;
} */