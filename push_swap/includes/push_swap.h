/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 10:09:24 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <limits.h>
# include <stdbool.h>

# define ERROR "Error\n"

# define ASC 1
# define DESC 0

typedef struct d_list
{
	int				content;
	int				n_cont;
	int 			curr_pos;
	bool 			direct_rotate;
	int				move_price;
	struct d_list	*next;
	struct d_list	*prev;
	struct d_list	*target;
}	t_dlist;

t_dlist	*read_input(int ac, char **av);
int		all_is_num(char **av, int ac);
int		has_duplicate(t_dlist *stack);
int		ft_isnum(char *s);
int		ft_atoi_custom(const char *str);
void	calculate_indexes(t_dlist **stack, int n);

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new_node);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new_node);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist	*ft_dlstnew(int content);
void	ft_dlst_free(t_dlist **lst);
int		ft_dlstlen(t_dlist *lst);
int		ft_med_count(t_dlist *lst, int len);
t_dlist	*ft_dlst_find_min(t_dlist *stack);

t_dlist	*ft_detach_node(t_dlist **stack, t_dlist *node);
void	ft_swap(t_dlist **stack);
void	ft_push(t_dlist **stack_from, t_dlist **stack_to);
void	ft_rotate(t_dlist **stack);
void	ft_reverse_rotate(t_dlist **stack);

void	ft_sa(t_dlist **stack_a);
void	ft_sb(t_dlist **stack_a);
void	ft_ss(t_dlist **stack_a, t_dlist **stack_b);
void	ft_pa(t_dlist **stack_a, t_dlist **stack_b);
void	ft_pb(t_dlist **stack_a, t_dlist **stack_b);
void	ft_ra(t_dlist **stack_a);
void	ft_rb(t_dlist **stack_a);
void	ft_rr(t_dlist **stack_a, t_dlist **stack_b);
void	ft_rra(t_dlist **stack_a);
void	ft_rrb(t_dlist **stack_a);
void	ft_rrr(t_dlist **stack_a, t_dlist **stack_b);

void	sort_stack(t_dlist **stack_a, t_dlist **stack_b);
void	sort_2(t_dlist **stack, int order);
void	sort_3(t_dlist **stack, int order);
int		quick_sort_a(t_dlist **stack_a, t_dlist **stack_b, int len);
int		quick_sort_b(t_dlist **stack_a, t_dlist **stack_b, int len);
int		sort_check(t_dlist *stack, int order, int len);
void	print_stack(t_dlist *stack);
void	big_sort(t_dlist **stack_a, t_dlist **stack_b);

/*TODO: remove those that not needed*/
void	set_mid(t_dlist *stack);
void	set_target(t_dlist *stack_a, t_dlist *stack_b);
void	calc_prices(t_dlist *stack_a, t_dlist *stack_b);
t_dlist	*find_candidate(t_dlist *stack_b);
void	move_candidate(t_dlist **stack_a, t_dlist **stack_b);
t_dlist	*find_first(t_dlist *stack);

#endif