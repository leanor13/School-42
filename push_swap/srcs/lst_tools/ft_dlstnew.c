/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:24:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/25 14:25:57 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

t_dlist	*ft_dlstnew(int content)
{
	t_dlist	*res;

	res = (t_dlist *)malloc(sizeof(t_dlist));
	if (!res)
		return (NULL);
	res -> content = content;
	res -> next = NULL;
	res -> prev = NULL;
	return (res);
}
