
#include <stdlib.h>
#include <stdio.h>

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

void    ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	t_list *curr;

	if (!begin_list || !f)
		return ;
	curr = begin_list;
	
	while (curr)
	{
		f(curr -> data);
		curr = curr -> next;
	}
}

void fun(void *i)
{
	printf("FUN working: %p\n", i);
}

int	main(void)
{
	t_list	*node0 = malloc(sizeof(t_list));
	t_list	*node1 = malloc(sizeof(t_list));
	t_list	*curr = malloc(sizeof(t_list));

	node0 -> data = (void *)1;
	node1 -> data = (void *)2;
	node1 -> next = NULL;
	node0 -> next = node1;

	curr = node0;
	while (curr)
	{
		printf("%ld\n", (intptr_t)(curr -> data));
		curr = curr -> next;
	}
	ft_list_foreach(node0, fun);
	curr = node0;
	while (curr)
	{
		printf("%ld\n", (intptr_t)(curr -> data));
		curr = curr -> next;
	}
	return (0);
}