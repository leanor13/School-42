/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/25 15:01:43 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# define ERROR_EMPTY_INPUT "Needed at least one integer"
# define ERROR_INVALID_CHARACTERS "Invalid input, only digits are allowed"
# define ERROR_DUPLICATE "Duplicate numbers are not allowed"
# define ERROR_MALLOC "Malloc error"

typedef struct d_list
{
	int				content;
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