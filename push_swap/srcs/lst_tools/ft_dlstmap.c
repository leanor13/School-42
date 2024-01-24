/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:26:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/24 13:39:07 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_start;
	t_list	*curr_new;
	void	*c;

	if (!lst || !f || !del)
		return (NULL);
	current = lst;
	new_start = NULL;
	while (current)
	{
		c = f(current -> content);
		curr_new = ft_lstnew(c);
		if (!curr_new)
		{
			ft_lstclear(&new_start, del);
			del(c);
			return (NULL);
		}
		ft_lstadd_back(&new_start, curr_new);
		current = current -> next;
	}
	return (new_start);
}

/* #include <stdio.h>

void	*ft_capital(void *s)
{
	size_t i;
	char *str = ft_strdup((char *)s);

	if (!str)
		return (NULL);

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

int	main(void)
{
	t_list	*elem0;
	t_list	*elem1;
	t_list	*elem2;
	t_list	*current;
	t_list	*new;

	char *content0 = ft_strdup("hello");
	char *content1 = ft_strdup("this is");
	char *content2 = ft_strdup("C");
	elem0 = ft_lstnew(content0);
	elem1 = ft_lstnew(content1);
	elem2 = ft_lstnew(content2);
	ft_lstadd_front(&elem0, elem1);
	ft_lstadd_front(&elem0, elem2);
	current = elem0;
	while (current)
	{
		printf("%s\n", (char *)(current -> content));
		current = current -> next;	
	}
	new = ft_lstmap(elem0, ft_capital, free);
	while (new)
	{
		printf("%s\n", (char *)(new -> content));
		new = new -> next;	
	}
	ft_lstclear(&new, free);
	return (0);
} */