/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:19:02 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 14:20:07 by yioffe           ###   ########.fr       */
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
		return ;
	pthread_mutex_lock(&philo->mutex_eating);
	gettimeofday(&current_time, NULL);
	gettimeofday(&philo->last_eat_time, NULL);
	philo_print("is eating", philo);
	philo_sleep(config->time_to_eat, config);
	increment_eat_counter(philo);
	pthread_mutex_unlock(&philo->mutex_eating);
}

static int	philo_take_single_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_print("has taken a fork", philo);
	philo_sleep(philo->config->time_to_die, philo->config);
	pthread_mutex_unlock(philo->left_fork);
	return (EXIT_FAILURE);
}

static int	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		philo_print("has taken a fork", philo);
		if (check_config_stop(philo->config))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo_print("has taken a fork", philo);
		if (check_config_stop(philo->config))
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
	}
	philo_print("has taken a fork", philo);
	return (0);
}

void	philo_take_forks_and_eat(t_philo *philo)
{
	if (check_config_stop(philo->config))
		return ;
	if (philo->left_fork == philo->right_fork)
	{
		if (philo_take_single_fork(philo))
			return ;
	}
	else
	{
		if (philo_take_forks(philo))
			return ;
		if (!check_config_stop(philo->config))
			philo_eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
