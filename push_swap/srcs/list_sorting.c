
#include "../includes/push_swap.h"

int	sort_check(t_dlist *stack, int order, int len)
{
	int	count;

	count = 0;
	while (stack->next && count < len)
	{
		if (order == ASC && (stack->content > stack->next->content))
			return (0);
		if (order == DESC && (stack->content < stack->next->content))
			return (0);
		count ++;
		stack = stack->next;
	}
	return (1);
}

void	sort_2(t_dlist **stack, int order)
{
	if (sort_check(*stack, order, 2))
		return ;
	if (order == ASC)
		ft_sa(stack);
	else
		ft_sb(stack);
}
void	sort_3(t_dlist **stack, int order)
{
	int	x;
	int	y;
	int	z;

	if (sort_check(*stack, order, 3))
		return ;
	x = (*stack)->n_cont;
	y = (*stack)->next->n_cont;
	z = (*stack)->next->next->n_cont;
	if (order == ASC)
	{
		if ((x < y && x < z) && y > z)
		{
			ft_sa(stack);
			ft_ra(stack);
		}
		else if (x < y && x > z)
				ft_rra(stack);
		else if (x < z && x > y)
				ft_sa(stack);
		else if (x > y && x > z)
		{
			ft_ra(stack);
			if (y > z)
				ft_sa(stack);
		}
	}
	else
	{
		if ((x > y && x > z) && y < z)
		{
			ft_sb(stack);
			ft_rb(stack);
		}
		else if (x > y && x < z)
				ft_rrb(stack);
		else if (x > z && x < y)
				ft_sb(stack);
		else if (x < y && x < z)
		{
			ft_rb(stack);
			if (y < z)
				ft_sb(stack);
		}
	}
}

int	quick_sort_a(t_dlist **stack_a, t_dlist **stack_b, int len)
{
	int		med;
	int		count;
	int		pushed;


	if (sort_check(*stack_a, ASC, len))
		return (1);
	count = len;
	if (len == 2)
	{
		sort_2(stack_a, ASC);
		return (1);
	}
	if (len == 3)
	{
		sort_3(stack_a, ASC);
		return (1);
	}
	pushed = 0;
	med = ft_med_count(*stack_a, len);
	if (!med)
		return (0);
	while (len != count / 2 + count % 2)
		if ((*stack_a)->n_cont < med && (len--))
			ft_pb(stack_a, stack_b);
		else if ((++pushed))
			ft_ra(stack_a);
	while (count / 2 + count % 2 != ft_dlstlen(*stack_a) && pushed --)
		ft_rra(stack_a);
	return (quick_sort_a(stack_a, stack_b, count / 2 + count % 2) 
			&& quick_sort_b(stack_a, stack_b, count / 2));
}
int	quick_sort_b(t_dlist **stack_a, t_dlist **stack_b, int len)
{
	int		med;
	int		count;
	int		pushed;

	if (sort_check(*stack_b, DESC, len))
	{
		while (len --)
			ft_pa(stack_a, stack_b);
	}
	if (len == 2)
	{
		sort_2(stack_b, DESC);
		return (1);
	}
	if (len == 3)
	{
		sort_3(stack_b, DESC);
		return (1);
	}
	pushed = 0;
	med = ft_med_count(*stack_b, len);
	if (!med)
		return (0);
	count = len;
	while (len != count / 2)
	{
		if ((*stack_b)->n_cont >= med && len --) 
			ft_pa(stack_a, stack_b);
		else if (++pushed)
			ft_rb(stack_b);
	}
	while (count / 2 != ft_dlstlen(*stack_b) && pushed--)
		ft_rrb(stack_b);
	return (quick_sort_a(stack_a, stack_b, count / 2 + count % 2) 
			&& quick_sort_b(stack_a, stack_b, count / 2));
}

void	sort_stack(t_dlist **stack_a, t_dlist **stack_b)
{
	int	size;

	(void)stack_b;
	size = ft_dlstlen(*stack_a);
	if (size == 2)
		sort_2(stack_a, ASC);
	else if (size == 3)
		sort_3(stack_a, ASC);
	else if (size == 6)
	{
		quick_sort_a(stack_a, stack_b, ft_dlstlen(*stack_a));
	}
	else
		ft_printf("Not supported length");
}
