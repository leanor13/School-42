/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:54:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/10 14:59:44 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// TODO: remove printf and other not allowed functions
// TODO: remove printf for put up/down fork
// TODO: fix case for 1 philo

void philo_print(const char *message, t_philo *philo)
{
    t_config *config = philo->config;
    struct timeval current_time;
	unsigned long long timestamp_in_ms;

    gettimeofday(&current_time, NULL);
    timestamp_in_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);

    pthread_mutex_lock(&config->mutex_write);

    ft_putnbr_fd(timestamp_in_ms, STDOUT_FILENO);
    write(STDOUT_FILENO, " Philosopher ", 13);

    ft_putnbr_fd(philo->id, STDOUT_FILENO);
    write(STDOUT_FILENO, " ", 1);

	while(*message)
	{
    	write(STDOUT_FILENO, message, 1);
		message ++;
	}
    write(STDOUT_FILENO, "\n", 1);

    pthread_mutex_unlock(&config->mutex_write);
}

void p_sleep(int duration_ms, t_config *config) {
    int elapsed = 0;
    while (elapsed < duration_ms && !config->stop) {
        usleep(1000);
        elapsed += 1;
    }
}

void philo_eat(t_philo *philo)
{
    t_config *config = philo->config;
	struct timeval current_time;
	long time_since_last_meal;

	if (philo->config->stop || !philo->alive)
			return;
    pthread_mutex_lock(&philo->mutex_eating);

	gettimeofday(&current_time, NULL);

	time_since_last_meal = time_diff_in_ms(philo->last_eat_time, current_time);

	// pthread_mutex_lock(&config->mutex_write);
	// printf("\n[PHILO] Philosopher %d is going to start eating.\n", philo->id);
    // printf("Time since last meal: %ld ms\n", time_since_last_meal);
    // printf("Current time: %ld ms\n", 
    //     (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	// pthread_mutex_unlock(&config->mutex_write);

    philo_print("is eating", philo);

    p_sleep(config->time_to_eat, config);

	gettimeofday(&current_time, NULL);  
	gettimeofday(&philo->last_eat_time, NULL);
    philo->eat_count++;

	// pthread_mutex_lock(&config->mutex_write);
	// printf("\n[PHILO] Philosopher %d finished eating, time updated.\n", philo->id);
    // printf("Current time: %ld ms, Last eat time set: %ld ms\n", 
    //     (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000),
    //     (philo->last_eat_time.tv_sec * 1000) + (philo->last_eat_time.tv_usec / 1000));
	// pthread_mutex_unlock(&config->mutex_write);

    pthread_mutex_unlock(&philo->mutex_eating);
}


void philo_take_forks_and_eat(t_philo *philo)
{
	if (philo->config->stop || !philo->alive)
            return;
	if (philo->left_fork == philo->right_fork) 
	{
        pthread_mutex_lock(philo->left_fork);
		p_sleep(philo->config->time_to_die, philo->config);
        pthread_mutex_unlock(philo->left_fork);
    }
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);

		philo_eat(philo);

		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		*philos;
	pthread_t	*threads;
	int			created_threads;
	pthread_t   monitor_thread;
	int			i;

	config = init_config(argc, argv);
	if (!config)
	{
		fprintf(stderr, "Error initializing configuration.\n");
		return (EXIT_FAILURE);
	}
	philos = initiate_philos(config);
	if (!philos)
	{
		free(config);
		fprintf(stderr, "Error initializing philosophers.\n");
		return (EXIT_FAILURE);
	}
	created_threads = create_threads(&threads, philos, config);
	if (created_threads != 0)
	{
		// Cleanup if thread creation failed
		i = 0;
		if (created_threads > 0)
		{
			while (i < created_threads)
			{
				pthread_join(threads[i], NULL);
				i++;
			}
		}
		cleanup(philos, threads, config);
		return (EXIT_FAILURE);
	}

	// check how to join this thread
	if (pthread_create(&monitor_thread, NULL, monitor_routine, config) != 0)
    {
        fprintf(stderr, "Failed to create monitor thread.\n");
        cleanup(philos, threads, config);
        return (EXIT_FAILURE);
    }
	// Join all threads
	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	pthread_join(monitor_thread, NULL);
	cleanup(philos, threads, config);
	return (EXIT_SUCCESS);
}
