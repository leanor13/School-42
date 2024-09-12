/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:53:37 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 16:53:03 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	death_check(t_philo *philo, t_config *config)
{
	long			time_since_last_eat;
	struct timeval	current_time;

	sem_wait(philo->sem_eating);
	gettimeofday(&current_time, NULL);
	time_since_last_eat = time_diff_in_ms(philo->last_eat_time, current_time);
	if (time_since_last_eat > config->time_to_die)
	{
		set_config_stop(config, true);
		philo_print("died", philo);
		sem_post(philo->sem_eating);
		return (EXIT_FAILURE);
	}
	sem_post(philo->sem_eating);
	return (EXIT_SUCCESS);
}

void	monitor_routine(t_config *config)
{
	int			done_philo;
	int			i;

	while (!check_config_stop(config))
	{
		done_philo = 0;
		for (i = 0; i < config->number_of_philos; i++)
		{
			if (death_check(&config->philos[i], config) == EXIT_FAILURE)
			{
				set_config_stop(config, true);
				kill_all_philos(config);
				exit(EXIT_FAILURE);
			}
			if (config->max_eat_times >= 0
				&& get_eat_counter(&config->philos[i]) >= config->max_eat_times)
			{
				done_philo++;
			}
		}
		if (config->max_eat_times >= 0 && done_philo == config->number_of_philos)
		{
			set_config_stop(config, true);
			kill_all_philos(config);
			exit(EXIT_SUCCESS);
		}
		usleep(MONITOR_FREQUENCY_US);
	}
}


void	philosopher_routine(t_philo *philo)
{
	t_config	*config;

	config = philo->config;
	if (!config)
		return;
	if (philo->id % 2 && config->number_of_philos > 1)
		philo_sleep(config->time_to_eat / 50, config);
	while (!check_config_stop(config))
	{
		if (check_config_stop(config))
			break ;
		philo_take_forks_and_eat(philo);
		if (check_config_stop(config))
			break ;
		philo_print("is sleeping", philo);
		philo_sleep(config->time_to_sleep, config);
		if (check_config_stop(config))
			break ;
		philo_print("is thinking", philo);
	}
	exit(0);
}

