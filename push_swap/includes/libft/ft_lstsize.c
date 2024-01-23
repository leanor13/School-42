/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:56:44 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/06 19:11:22 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*current;

	len = 0;
	current = lst;
	while (current != NULL)
	{
		len ++;
		current = current -> next;
	}
	return (len);
}

/* #include <stdio.h>

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

	// Print list length
	printf("length: %d\n", ft_lstsize(lst));


	return 0;
} */