/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:27:07 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/19 17:23:58 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <limits.h>
# include <stdbool.h>

# define ERROR "Error\n"

# define A 0
# define B 1
# define PRINT false
# define SILENT true

typedef struct d_list
{
	int				content;
	int				curr_pos;
	bool			direct_rotate;
	int				move_price;
	struct d_list	*next;
	struct d_list	*prev;
	struct d_list	*target;
}					t_dlist;

t_dlist				*read_input(int ac, char **av);
int					all_is_num(char **av, int ac);
int					has_duplicate(t_dlist *stack);
int					ft_isnum(char *s);
int					ft_atoi_custom(const char *str);
void				calculate_indexes(t_dlist **stack, int n);

void				ft_dlstadd_back(t_dlist **lst, t_dlist *new_node);
void				ft_dlstadd_front(t_dlist **lst, t_dlist *new_node);
t_dlist				*ft_dlstlast(t_dlist *lst);
void				ft_dlst_free(t_dlist **lst);
int					ft_dlstlen(t_dlist *lst);
t_dlist				*ft_dlst_find_min(t_dlist *stack);
t_dlist				*create_node(t_dlist *stack, char *av);

void				ft_swap(t_dlist **stack);
void				ft_push(t_dlist **stack_from, t_dlist **stack_to);
void				ft_rotate(t_dlist **stack);
void				ft_reverse_rotate(t_dlist **stack);

void				ft_s(t_dlist **stack, int where, bool silent);
void				ft_p(t_dlist **stack_a, t_dlist **stack_b, int where, bool silent);
void				ft_r(t_dlist **stack, int where, bool silent);
void				ft_rr(t_dlist **stack_a, int where, bool silent);
void				ft_ss(t_dlist **stack_a, t_dlist **stack_b, bool silent);
void				ft_rr_both(t_dlist **stack_a, t_dlist **stack_b, bool silent);
void				ft_rrr(t_dlist **stack_a, t_dlist **stack_b, bool silent);

void				sort_stack(t_dlist **stack_a, t_dlist **stack_b);
void				sort_2(t_dlist **stack);
void				sort_3(t_dlist **stack);
int					sort_check(t_dlist *stack);
void				big_sort(t_dlist **stack_a, t_dlist **stack_b);

void				set_rotation_dir(t_dlist *stack);
void				set_target(t_dlist *stack_a, t_dlist *stack_b);
void				calc_prices(t_dlist *stack_a, t_dlist *stack_b);
t_dlist				*find_candidate(t_dlist *stack_b);
void				finish_rotating(t_dlist **stack_a, t_dlist **stack_b,
						t_dlist *candidate);

#endif