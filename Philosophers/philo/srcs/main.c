/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 13:22:25 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// TODO: remove printf and other not allowed functions
// TODO: remove printf for put up/down fork
// TODO: add limits (60 for time and 200 for philo)
// TODO: fix normi
// TODO: put back Makefile flags
// TODO: put all in philo dir

void	philo_print(const char *message, t_philo *philo)
{
	t_config			*config;
	struct timeval		current_time;
	unsigned long long	timestamp_in_ms;

	config = philo->config;
	gettimeofday(&current_time, NULL);
	timestamp_in_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec
			/ 1000);
	pthread_mutex_lock(&config->mutex_write);
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
	pthread_mutex_unlock(&config->mutex_write);
}

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

void	philo_eat(t_philo *philo)
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

static int	start_monitor_thread(t_config *config, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, monitor_routine, config) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	pthread_t	*threads;
	pthread_t	monitor_thread;
	int			created_threads;

	config = init_config(argc, argv);
	if (!config)
		return (EXIT_FAILURE);
	philos = initiate_philos(config);
	if (!philos)
		return (free(config), EXIT_FAILURE);
	created_threads = create_threads(&threads, philos, config);
	if (created_threads != EXIT_SUCCESS)
		return (handle_thread_creation_error(philos, threads, config,
				created_threads));
	if (start_monitor_thread(config, &monitor_thread) != EXIT_SUCCESS)
	{
		cleanup(philos, threads, config);
		return (EXIT_FAILURE);
	}
	join_threads(threads, config->number_of_philos);
	pthread_join(monitor_thread, NULL);
	cleanup(philos, threads, config);
	return (EXIT_SUCCESS);
}
