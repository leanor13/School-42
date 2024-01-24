/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/24 15:19:59 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# define ERROR_EMPTY_INPUT "Needed at least one integer"
# define ERROR_INVALID_INPUT "Invalid input, only digits are allowed"

typedef struct d_list
{
	int				num;
	struct d_list	*next;
	struct d_list	*prev;
}	t_dlist;

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new_node);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new_node);
void	ft_dlstclear(t_dlist **lst, void (*del)(void*));
void	ft_dlstdelone(t_dlist *lst, void (*del)(void*));
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist	*ft_dlstnew(int content);
int		ft_dlstsize(t_dlist *lst);
void	ft_dlst_free(t_dlist **lst);

#endif