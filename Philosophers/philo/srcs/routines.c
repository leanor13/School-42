/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:53:37 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/11 20:06:41 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *monitor_routine(void *params) 
{
	t_config *config;
	t_philo *philo;
	struct timeval current_time;
	int	done_philo;
	int	eat_counter;
	long time_since_last_eat;

	config = (t_config *)params;
	while (!check_config_stop(config)) 
	{
		philo = config->first_philo;
		done_philo = 0;
		while (philo) 
		{
			pthread_mutex_lock(&philo->mutex_eating);
			gettimeofday(&current_time, NULL);
			time_since_last_eat = time_diff_in_ms(philo->last_eat_time, current_time);
			if (time_since_last_eat > config->time_to_die) 
			{
				set_config_stop(config, true);
				philo_print("died", philo);
				pthread_mutex_unlock(&philo->mutex_eating);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->mutex_eating);
			eat_counter = get_eat_counter(philo);
			if (config->max_eat_times >= 0 && eat_counter >= config->max_eat_times)
				done_philo ++;
			philo = philo->next;
		}
		if (config->max_eat_times >= 0 && done_philo == config->number_of_philosophers)
		{
			set_config_stop(config, true);
			return (NULL);
		}
		usleep(100); 
	}
	return (NULL);
}

void *philosopher_routine(void *params) {
	t_philo			*philo;
	t_config		*config;
	struct timeval	start_sleep; 
	struct timeval	end_sleep;

	philo = (t_philo *)params;
	config = philo->config;
	if (!config)
		return (NULL);
	if (philo->id % 2 && config->number_of_philosophers > 1)
		philo_sleep(config->time_to_eat / 50, config);
	while (!check_config_stop(config))
	{
		if (check_config_stop(config))
			break;
		philo_take_forks_and_eat(philo);
		if (check_config_stop(config))
			break;
		philo_print("is sleeping", philo);
		gettimeofday(&start_sleep, NULL);
		philo_sleep(config->time_to_sleep, config);
		gettimeofday(&end_sleep, NULL);
		if (check_config_stop(config))
			break;
		philo_print("is thinking", philo);
	}
	return (NULL);
}