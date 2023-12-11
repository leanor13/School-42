
#include "list.h"
#include <stdio.h>

int descending(int a, int b)
{
	return (a >= b);
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    int  swap;
    int  swap_done = 1;
    t_list  *lst_start;

    lst_start = lst;
    while (swap_done)
    {
        swap_done = 0;
        lst = lst_start;
        while (lst -> next)
        {
            if (!cmp(lst -> data, lst -> next -> data))
            {
                swap_done = 1;
                swap = lst -> data;
                lst -> data = lst -> next -> data;
                lst -> next -> data = swap;
            }
            lst = lst -> next;
        }
    }
    return (lst_start);
}

int main(void)
{
    t_list node0;
    t_list node1;
    t_list node2;
    t_list *lst;
    t_list *sorted_lst;

    node2.data = 1;
    node2.next = NULL;
    node1.data = 1;
    node1.next = &node2;
    node0.data = 5;
    node0.next = &node1;
    lst = &node0;

    printf("d1: %d, d2: %d, d3: %d\n", 
        lst -> data, lst -> next -> data, lst -> next -> next -> data);
    sorted_lst = sort_list(lst, descending);
    printf("Sorted: d1: %d, d2: %d, d3: %d\n", 
        sorted_lst -> data, sorted_lst -> next -> data, sorted_lst -> next -> next -> data);
    return (0);
}