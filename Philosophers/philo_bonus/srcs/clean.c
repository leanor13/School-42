/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:55:58 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 13:56:15 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philos(t_philo *philos)
{
	t_philo	*current;
	t_philo	*next;

	current = philos;
	if (!philos)
		return ;
	while (current != NULL)
	{
		next = current->next;
		pthread_mutex_destroy(&current->mutex_eating);
		pthread_mutex_destroy(&current->mutex_counter);
		free(current);
		current = next;
	}
}

void	cleanup(t_philo *philos, pthread_t *threads, t_config *config)
{
	int	i;

	if (threads)
		free(threads);
	if (philos)
		free_philos(philos);
	if (config)
	{
		i = 0;
		while (i < config->number_of_philos)
		{
			pthread_mutex_destroy(&config->forks[i]);
			i ++;
		}
		pthread_mutex_destroy(&config->mutex_stop);
		pthread_mutex_destroy(&config->mutex_write);
		free(config->forks);
		free(config);
	}
}

int	handle_thread_creation_error(t_philo *philos, pthread_t *threads,
		t_config *config, int created_threads)
{
	if (created_threads > 0)
		join_threads(threads, created_threads);
	cleanup(philos, threads, config);
	return (EXIT_FAILURE);
}
