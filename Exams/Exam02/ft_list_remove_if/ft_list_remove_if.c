
#include <stdio.h>
#include <stdlib.h>

typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *))
{
	t_list	*curr;
	t_list	*temp;
	t_list	*prev = NULL;

	if (!begin_list || !*begin_list)
		return ;
	curr = *begin_list;
	while (curr && cmp(curr->data, data_ref))
	{
		temp = curr -> next;
		free(curr);
		*begin_list = temp;
		curr = temp;
	}
	while (curr)
	{
		if (cmp(curr->data, data_ref))
		{
			temp = curr -> next;
			free(curr);
			prev -> next = temp;
			curr = temp;
		}
		else
		{
			prev = curr;
			curr = curr -> next;
		}
	}
}

int	comp(void *a, void *b)
{
	return ((intptr_t)a == (intptr_t)b);
}

int	main(void)
{
	t_list	*node0 = malloc(sizeof(t_list));
	t_list	*node1 = malloc(sizeof(t_list));
	t_list	*node2 = malloc(sizeof(t_list));
	t_list	*curr;

	if (!node0 || !node1 || !node2) 
	{
        return 1;
    }

	node2 -> data = (void *)1;
	node1 -> data = (void *)2;
	node0 -> data = (void *)8;
	node2 -> next = NULL;
	node1 -> next = node2;
	node0 -> next = node1;

	curr = node0;
	while (curr)
	{
		printf("%ld\n", (intptr_t)curr->data);
		curr = curr -> next;
	}
	ft_list_remove_if(&node0, (void *)8, comp);
	curr = node0;
	printf("New list:\n");
	while (curr)
	{
		printf("%ld\n", (intptr_t)curr->data);
		curr = curr -> next;
	}
	return (0);
}