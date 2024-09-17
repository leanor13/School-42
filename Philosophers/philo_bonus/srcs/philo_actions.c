/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:19:02 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/17 14:43:35 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
	t_config	*config;

	config = philo->config;
	if (check_config_stop(config))
		return ;
	sem_wait(config->sem_killer);
	gettimeofday(&philo->last_eat_time, NULL);
	philo_print("is eating", philo);
	sem_post(config->sem_killer);
	philo_sleep(config->time_to_eat, config);
	philo->eat_counter++;
	if (config->max_eat_times >= 0
		&& philo->eat_counter == config->max_eat_times)
		sem_post(config->sem_fed_up);
}

static int	philo_take_forks(t_philo *philo)
{
	t_config	*config;

	config = philo->config;
	sem_wait(config->forks_sem);
	philo_print("has taken a fork", philo);
	if (check_config_stop(config))
	{
		sem_post(config->forks_sem);
		return (EXIT_FAILURE);
	}
	sem_wait(config->forks_sem);
	philo_print("has taken a fork", philo);
	return (EXIT_SUCCESS);
}

void	philo_take_forks_and_eat(t_philo *philo)
{
	if (check_config_stop(philo->config))
		return ;
	if (philo_take_forks(philo) == EXIT_FAILURE)
		return ;
	if (!check_config_stop(philo->config))
		philo_eat(philo);
	sem_post(philo->config->forks_sem);
	sem_post(philo->config->forks_sem);
}

void	philo_print(const char *message, t_philo *philo)
{
	t_config			*config;
	struct timeval		current_time;
	unsigned long long	timestamp_in_ms;
	static int			i;

	if (i == 1)
		return ;
	if (message[0] == 'd')
		i = 1;
	config = philo->config;
	gettimeofday(&current_time, NULL);
	timestamp_in_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec
			/ 1000);
	sem_wait(config->sem_write);
	printf("%llu %i %s\n", timestamp_in_ms, philo->id, message);
	sem_post(config->sem_write);
}
