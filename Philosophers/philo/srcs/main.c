/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/07 16:06:31 by yioffe           ###   ########.fr       */
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

int	init_input(int ac, char **av)
{
	int	arguments[ac - 1];
	int	i;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	i = 0;
	while (i < ac - 1)
	{
		arguments[i] = atoi_positive(av[i + 1]);
		if (arguments[i] < 0)
			return (EXIT_FAILURE);
		if (i < 3 && arguments[i] == 0)
			return (EXIT_FAILURE);
		ac --;
	}
	return (EXIT_SUCCESS);
}	

int	main(int ac, char **av)
{
	pthread_t thread_id; 

	if (init_input(ac, av) == EXIT_FAILURE);
		return (EXIT_FAILURE);
	printf("Before Thread\n"); 
	pthread_create(&thread_id, NULL, myThreadFun, NULL); 
	pthread_join(thread_id, NULL); 
	printf("After Thread\n"); 
	exit(0);
}