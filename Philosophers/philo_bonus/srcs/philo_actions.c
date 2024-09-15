/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:19:02 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/15 15:07:12 by yioffe           ###   ########.fr       */
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
	t_config		*config;
	//struct timeval	current_time;

	config = philo->config;
	if (check_config_stop(config))
		return;
	//gettimeofday(&current_time, NULL);
	gettimeofday(&philo->last_eat_time, NULL);
	//philo_print_debug("eat time updated", philo);
	philo_print("is eating", philo);
	philo_sleep(config->time_to_eat, config);
	philo->eat_counter ++;
	//increment_eat_counter(philo);
}


static int	philo_take_forks(t_philo *philo)
{
	t_config *config = philo->config;

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
		return;
	if (philo_take_forks(philo))
		return;
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

	config = philo->config;
	gettimeofday(&current_time, NULL);
	timestamp_in_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	sem_wait(config->sem_write);
	ft_putnbr_fd(timestamp_in_ms, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	ft_putnbr_fd(philo->id, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	while (*message)
	{
		write(STDOUT_FILENO, message, 1);
		message++;
	}
	write(STDOUT_FILENO, "\n", 1);
	sem_post(config->sem_write);
}

