/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:19:02 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 15:55:23 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(int duration_ms, t_config *config)
{
	int				elapsed_time_ms;
	struct timeval	start_time;
	struct timeval	current_time;

	elapsed_time_ms = 0;
	gettimeofday(&start_time, NULL);
	while ((elapsed_time_ms < duration_ms) && !check_config_stop(config))
	{
		usleep(500);
		gettimeofday(&current_time, NULL);
		elapsed_time_ms = time_diff_in_ms(start_time, current_time);
	}
}

static void	philo_eat(t_philo *philo)
{
	t_config		*config;
	struct timeval	current_time;

	config = philo->config;
	if (check_config_stop(config))
		return;
	sem_wait(philo->sem_eating);
	gettimeofday(&current_time, NULL);
	gettimeofday(&philo->last_eat_time, NULL);
	philo_print("is eating", philo);
	philo_sleep(config->time_to_eat, config);
	increment_eat_counter(philo);
	sem_post(philo->sem_eating);
}


static int	philo_take_forks(t_philo *philo)
{
	t_config *config = philo->config;

	sem_wait(config->forks);
	philo_print("has taken a fork", philo);
	if (check_config_stop(config))
	{
		sem_post(config->forks);
		return (EXIT_FAILURE);
	}
	sem_wait(config->forks);
	philo_print("has taken a fork", philo);
	return (EXIT_SUCCESS);
}

void	philo_take_forks_and_eat(t_philo *philo)
{
	if (check_config_stop(philo->config))
		return;
	if (philo_take_forks(philo))
		return;
	if (!check_config_stop(philo->config))
		philo_eat(philo);
	sem_post(philo->config->forks);
	sem_post(philo->config->forks);
}

