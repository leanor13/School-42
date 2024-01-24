/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:11:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/24 13:38:57 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	if (!lst || !f)
		return ;
	current = lst;
	while (current)
	{
		f(current -> content);
		current = current -> next;
	}
}

/* #include <stdio.h>

void	ft_put_lst_el(void *ele)
{
	ft_putstr_fd((char *)ele, 1);
}

int	main(void)
{
	t_list	*elem0;
	t_list	*elem1;
	t_list	*elem2;
	t_list	*current;

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
	ft_lstiter(elem0, ft_put_lst_el);
	ft_lstclear(&elem0, free);
	return (0);
} */