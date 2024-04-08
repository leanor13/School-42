/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/08 10:57:04 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *myThreadFun(void *arg) 
{ 
	(void)arg;
	sleep(1);
	printf("Printing Hello Philo from Thread \n"); 
	sleep(3);
	return NULL; 
}

t_philo *initiate(int *arg)
{
    t_philo *philos;
    int     num;
    int     i;
    t_philo temp;

    num = arg[0];
    philos = malloc(num * sizeof(t_philo));
    temp.
    if (!philos)
        return (NULL);
    while (i < num)
    {
        philos
    }
}

t_philo	*init_input(int ac, char **av)
{
	int	    arguments[ac - 1];
	int	    i;
    t_philo *philos;

	if (ac < 5 || ac > 6)
		return (NULL);
	i = 0;
	while (i < ac - 1)
	{
		arguments[i] = atoi_positive(av[i + 1]);
		if (arguments[i] < 0)
			return (NULL);
		if (i < 3 && arguments[i] == 0)
			return (NULL);
		ac --;
	}
    philos = initiate(arguments);
	return (philos);
}	

int	main(int ac, char **av)
{
	pthread_t   thread_id;
    t_philo     *philos; 

    philos = init_input(ac, av);
	if (philos == NULL)
		return (EXIT_FAILURE);
	printf("Before Thread\n"); 
	pthread_create(&thread_id, NULL, myThreadFun, NULL); 
	pthread_join(thread_id, NULL); 
	printf("After Thread\n");
    free(philos);
	return (EXIT_SUCCESS);
}