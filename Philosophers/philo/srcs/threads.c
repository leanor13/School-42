/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:15:06 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/13 11:05:45 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	join_threads(pthread_t *threads, int created_threads)
{
	int	i;

	i = 0;
	while (i < created_threads)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	start_monitor_thread(t_config *config, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, monitor_routine, config) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_threads(pthread_t **threads, t_philo *philos, t_config *config)
{
	int		i;
	t_philo	*current;

	current = philos;
	i = 0;
	*threads = malloc(sizeof(pthread_t) * config->number_of_philos);
	if (!*threads)
	{
		return (-1);
	}
	while (i < config->number_of_philos)
	{
		pthread_create(&(*threads)[i], NULL, philosopher_routine, current);
		i++;
		current = current->next;
	}
	return (0);
}
