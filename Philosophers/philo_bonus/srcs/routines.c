/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:53:37 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/13 14:30:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	death_check(t_philo *philo, t_config *config)
{
	long			time_since_last_eat;
	struct timeval	current_time;

	//philo_print("Trying to check death for", philo);
	sem_wait(philo->sem_eating);
	//philo_print_debug("CHECKING", philo);
	gettimeofday(&current_time, NULL);
	time_since_last_eat = time_diff_in_ms(philo->last_eat_time, current_time);
	if (time_since_last_eat > config->time_to_die)
	{
		//philo_print_debug("KILLING", philo);
		set_config_stop(config, true);
		philo_print("died", philo);
		sem_post(philo->sem_eating);
		return (EXIT_FAILURE);
	}
	sem_post(philo->sem_eating);
	//philo_print_debug("check done", philo);
	return (EXIT_SUCCESS);
}

void	*monitor_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (1)
	{
		if (check_config_stop(philo->config))
			return (NULL);
		if (death_check(philo, philo->config) == EXIT_FAILURE)
		{
			kill_all_philos(philo->config);
			exit(EXIT_FAILURE);
		}
		usleep(MONITOR_FREQUENCY_US);
	}
}



void	philosopher_routine(t_philo *philo)
{
	t_config	*config;
	pthread_t monitor_thread;

    if (pthread_create(&monitor_thread, NULL, monitor_routine, (void *)philo) != 0) {
        exit(EXIT_FAILURE);
    }
    pthread_detach(monitor_thread);
	config = philo->config;
	if (!config)
		return;
	if (philo->id % 2)
		philo_sleep(1, config);
	while (!check_config_stop(config))
	{
		if (check_config_stop(config))
			break ;
		philo_take_forks_and_eat(philo);
		if (check_config_stop(config))
			break ;
		sem_wait(philo->sem_eating);
		//philo_print_debug("before going to sleep", philo);
		sem_post(philo->sem_eating);
		philo_print("is sleeping", philo);
		philo_sleep(config->time_to_sleep, config);
		if (check_config_stop(config))
			break ;
		philo_print("is thinking", philo);
	}
	exit(EXIT_SUCCESS);
}

